#include "debugger.hpp"

#include <functional>
#include <iomanip>
#include <sstream>
#include <array>
#include <SFML/Graphics/Color.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

// The constructor implementation is moved from the header
Debugger::Debugger(const std::string& filename) :
    romFilename(filename),
    emu(std::make_shared<Emulator>(filename)),
    debugContext(emu->getDebugContext())
{
    std::cout << "Debugger created" << std::endl;

    if (!tile_texture.resize({TILE_DATA_WIDTH_PX, TILE_DATA_HEIGHT_PX})) {
        std::cerr << "Failed to resize tile_texture" << std::endl;
    }

    tile_pixel_buffer.resize(TILE_DATA_WIDTH_PX * TILE_DATA_HEIGHT_PX * 4);

    // Start the emulator thread right after setup
    emu_thread = std::thread(&Debugger::emulator_thread_loop, this);
}

// The new destructor to safely stop the thread
Debugger::~Debugger() {
    shutdown_thread = true;
    if (emu_thread.joinable()) {
        emu_thread.join();
    }
}

uint32_t Debugger::getCurrentFrame() const {
    return emu->getCurrentFrame();
}

void Debugger::emulator_thread_loop() {
    while (!shutdown_thread) {
        if (emu_running) {
            // Lock once before running a batch of instructions.
            std::lock_guard<std::mutex> lock(emu_mutex);

            // A "timeslice" or batch size. You can tune this number.
            // It's the number of instructions to run before releasing the lock.
            const int instructions_per_slice = 1;

            for (int i = 0; i < instructions_per_slice; ++i) {
                if (breakpoints.count(this->getCurrentInstruction())) {
                    emu_running = false;
                    break; // Stop this batch if we hit a breakpoint
                }
                emu->run_one();
            }
        }

        // Briefly pause to allow the UI thread a chance to acquire the lock.
        // This prevents the emulator thread from hogging the CPU.
        std::this_thread::yield();
    }
}

void Debugger::render() {
    std::lock_guard<std::mutex> lock(emu_mutex);
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags host_window_flags = 0;
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    host_window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::Begin("Main", nullptr , host_window_flags);

    // render_disassembly_panel();
    // render_tile_data_panel();
    render_command_prompt();
    // render_registers_panel();
    // render_hex_view();

    ImGui::End();
}

void Debugger::render_tile_data_panel() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    constexpr float disassembly_width = 350.0f;
    constexpr float right_panel_width = 320.0f;
    const float prompt_height = ImGui::GetTextLineHeightWithSpacing() + 20;
    constexpr float margin = 16.0f;

    const auto panel_pos = ImVec2(main_pos.x + disassembly_width + margin, main_pos.y + 5.0f);
    const auto panel_size = ImVec2(main_size.x - disassembly_width - right_panel_width - (2 * margin), main_size.y - prompt_height - 10.0f);

    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                                              ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar;
    ImGui::SetNextWindowPos(panel_pos);
    ImGui::SetNextWindowSize(panel_size);

    ImGui::Begin("Tile Data", nullptr, window_flags);

    const sf::Color tile_colors[4] = {
        sf::Color(155, 188, 15),
        sf::Color(139, 172, 15),
        sf::Color(48, 98, 48),
        sf::Color(15, 56, 15)
    };

    const uint16_t startLocation = 0x8000;
    const unsigned int view_width_px = 16 * 8;

    for (int tile_idx = 0; tile_idx < 384; ++tile_idx) {
        const int tile_x_base = (tile_idx % 16) * 8;
        const int tile_y_base = (tile_idx / 16) * 8;

        for (int row = 0; row < 8; ++row) {
            const uint16_t row_addr = startLocation + (tile_idx * 16) + (row * 2);
            const uint8_t byte1 = debugContext.mmu.get().read_data(row_addr);
            const uint8_t byte2 = debugContext.mmu.get().read_data(row_addr + 1);

            for (int col = 0; col < 8; ++col) {
                const int bit = 7 - col;
                const uint8_t hi_bit = (byte2 >> bit) & 1;
                const uint8_t lo_bit = (byte1 >> bit) & 1;
                const uint8_t color_index = (hi_bit << 1) | lo_bit;

                const int px = tile_x_base + col;
                const int py = tile_y_base + row;
                const size_t index = (py * view_width_px + px) * 4;

                const sf::Color& color = tile_colors[color_index];
                tile_pixel_buffer[index]     = color.r;
                tile_pixel_buffer[index + 1] = color.g;
                tile_pixel_buffer[index + 2] = color.b;
                tile_pixel_buffer[index + 3] = color.a;
            }
        }
    }

    tile_texture.update(tile_pixel_buffer.data());

    const float available_width = ImGui::GetContentRegionAvail().x;
    const float scale = available_width / view_width_px;

    ImGui::Image(tile_texture, ImVec2(view_width_px * scale, (24 * 8) * scale));

    ImGui::End();
}

void Debugger::render_hex_view() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    const float promptPadding = 20.0f;
    const float prompt_height = ImGui::GetTextLineHeightWithSpacing() + promptPadding;
    const float panelHeight = main_size.y - 200.0f - prompt_height;
    constexpr float panelWidth = 340.0f;

    const auto panel_pos = ImVec2(main_pos.x + main_size.x - panelWidth, main_pos.y + 200.0f);
    const auto panel_size = ImVec2(panelWidth, panelHeight);

    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                                              ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(panel_pos);
    ImGui::SetNextWindowSize(panel_size);

    ImGui::Begin("Hex Viewer", nullptr, window_flags);

    uint16_t curr_addr = hexview_curr_mem;
    for (unsigned line = 0; line < hexview_num_lines; line++) {
        std::ostringstream currLine;
        currLine << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << curr_addr << ":";
        ImGui::TextColored(ImVec4(1, 1, 0, 1), currLine.str().c_str());

        currLine.clear();
        currLine.str("");

        ImGui::SameLine(70.0f);

        for (unsigned loc = 0; loc < hexview_num_cols; loc++) {
            currLine << std::hex << std::uppercase << std::setw(2) << static_cast<unsigned>(debugContext.mmu.get().read_data(curr_addr)) << "  ";
            curr_addr++;
        }
        ImGui::TextColored(ImVec4(1, 1, 1, 0.9), currLine.str().c_str());
    }

    ImGui::End();
}

void Debugger::render_registers_panel() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    constexpr float panelHeight = 200.0f;
    constexpr float panelWidth = 340.0f;

    const auto panel_pos = ImVec2(main_pos.x + main_size.x - panelWidth, main_pos.y);
    constexpr auto panel_size = ImVec2(panelWidth, panelHeight);

    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                                              ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(panel_pos);
    ImGui::SetNextWindowSize(panel_size);

    auto renderReg = [&](const std::string& label, const REG_TYPE value) {
        ImGui::TableNextColumn();
        ImGui::Text("%s:", label.c_str());
        ImGui::SameLine(50.0f);
        const std::string formatString = (value >= REG_TYPE::RT_AF) ? "0x%04X" : "0x%02X";
        ImGui::TextColored(ImVec4(1, 0, 0, 1), formatString.c_str(), debugContext.regs.get().read_register(value));
    };

    auto renderMem = [&](const std::string& label, const uint16_t address) {
        ImGui::TableNextColumn();
        ImGui::Text("%s:", label.c_str());
        ImGui::SameLine(90.0f);
        static const std::string formatString = "0x%02X";
        ImGui::TextColored(ImVec4(1, 0, 0, 1), formatString.c_str(),
                           debugContext.mmu.get().read_data(address));
    };

    static constexpr uint16_t LCDC_addr = 0xFF40;
    static constexpr uint16_t STAT_addr = 0xFF41;
    static constexpr uint16_t LY_addr   = 0xFF44;
    static constexpr uint16_t IE_addr   = 0xFFFF;
    static constexpr uint16_t IF_addr   = 0xFF0F;

    constexpr auto flagSetColor = ImVec4(1, 0, 1, 1);
    constexpr auto flagUnsetColor = ImVec4(0.7, 0.7, 0.7, 1);

    const auto zColor = (debugContext.regs.get().flags.z()) ? flagSetColor : flagUnsetColor;
    const auto nColor = (debugContext.regs.get().flags.n()) ? flagSetColor : flagUnsetColor;
    const auto hColor = (debugContext.regs.get().flags.h()) ? flagSetColor : flagUnsetColor;
    const auto cColor = (debugContext.regs.get().flags.c()) ? flagSetColor : flagUnsetColor;

    ImGui::Begin("Registers", nullptr, window_flags);
        if (ImGui::BeginTable("RegSplit", 3, ImGuiTableFlags_None)) {

            ImGui::TableSetupColumn("CPU Reg", ImGuiTableColumnFlags_WidthFixed, 145.0f);
            ImGui::TableSetupColumn("Mem Reb", ImGuiTableColumnFlags_WidthFixed, 145.0f);
            ImGui::TableSetupColumn("Flags", ImGuiTableColumnFlags_WidthFixed, 60.0f);

            constexpr float flagPadding = 10.0f;
            renderReg("AF", REG_TYPE::RT_AF);
            renderMem("LCDC", LCDC_addr);

            ImGui::TableNextColumn();
            ImGui::SameLine(flagPadding);
            ImGui::TextColored(zColor, "Z");

            renderReg("BC", REG_TYPE::RT_BC);
            renderMem("STAT", STAT_addr);

            ImGui::TableNextColumn();
            ImGui::SameLine(flagPadding);
            ImGui::TextColored(nColor, "N");

            renderReg("DE", REG_TYPE::RT_DE);
            renderMem("LY", LY_addr);

            ImGui::TableNextColumn();
            ImGui::SameLine(flagPadding);
            ImGui::TextColored(hColor, "H");

            renderReg("HL", REG_TYPE::RT_HL);
            renderMem("TEMP", 0x0);

            ImGui::TableNextColumn();
            ImGui::SameLine(flagPadding);
            ImGui::TextColored(cColor, "C");

            renderReg("SP", REG_TYPE::RT_SP);
            renderMem("IE", IE_addr);

            ImGui::TableNextColumn();
            renderReg("PC", REG_TYPE::RT_PC);
            renderMem("IF", IF_addr);
        }
        ImGui::EndTable();
    ImGui::End();
}

void Debugger::handle_command(char* commandBuffer) {

    std::string command(commandBuffer);

    const size_t first = command.find_first_not_of(" \t\n\r");
    // ReSharper disable once CppTooWideScopeInitStatement
    const size_t last = command.find_last_not_of(" \t\n\r");
    if (std::string::npos == first || std::string::npos == last) {
        command = prevCommandBuffer;
    }
    else {
        command = command.substr(first, last - first + 1);
    }


    std::stringstream ss(command);
    std::string token;
    ss >> token;

    if (token == "s")       this->stepIn();
    else if (token == "n")  this->stepOver();
    else if (token == "f")  this->stepOut();
    else if (token == "c")  this->runContinue();
    else if (token == "b") {
        uint16_t addr; ss >> std::hex >> addr;
        this->toggleBreakpoint(addr);
    }
    else if (token == "r") {
        this->reload_rom();
    }
    else if (token == "h") {
        uint16_t addr; ss >> std::hex >> addr;
        this->hexview_curr_mem = addr;
    }
    else if (token == "speed") {
        uint64_t speed; ss >> speed;
        std::cout << speed << std::endl;
        this->instPerFrame = speed;
    }
    strcpy(prevCommandBuffer, command.c_str());
    strcpy(commandBuffer, "");
}

void Debugger::render_command_prompt() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    const float prompt_height = ImGui::GetTextLineHeightWithSpacing() + 20;

    const auto panel_pos = ImVec2(main_pos.x, main_pos.y + main_size.y - prompt_height);
    const auto panel_size = ImVec2(main_size.x, prompt_height);

    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                              ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                                              ImGuiWindowFlags_NoBackground;
    ImGui::SetNextWindowPos(panel_pos);
    ImGui::SetNextWindowSize(panel_size);

    ImGui::Begin("Command Prompt", nullptr, window_flags);
    char commandBuffer[256] = "";
    ImGui::PushItemWidth(-1.0f);
    if (emu_running) {
        if (ImGui::Button("Break", ImVec2(-1.0f, 0.0f))) {
            emu_running = false;
        }
    } else {
        // Otherwise, show the command input prompt
        static char commandBuffer[256] = ""; // Make buffer static
        if (ImGui::InputTextWithHint("##Prompt", "Enter command...", commandBuffer, sizeof(commandBuffer),
                ImGuiInputTextFlags_EnterReturnsTrue)) {
            handle_command(commandBuffer);
                }
        ImGui::SetKeyboardFocusHere(-1);
    }
    ImGui::PopItemWidth();
    ImGui::End();
}

void Debugger::render_disassembly_panel() {

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    constexpr float panel_width = 360.0f;
    const float prompt_height = ImGui::GetTextLineHeightWithSpacing() + 20;

    const auto panel_pos = ImVec2(main_pos.x + 8.0f, main_pos.y + 5.0f);
    const auto panel_size = ImVec2(panel_width, main_size.y - prompt_height);


    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse |
                                              ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(panel_pos);
    ImGui::SetNextWindowSize(panel_size);

    ImGui::Begin("Disassembly", nullptr, window_flags);

    uint16_t addr = getCurrentInstruction();
    for (unsigned line = 0; line < disassembler_num_lines; line++) {
        const uint8_t opcode = debugContext.mmu.get().read_data(addr);
        const auto &[mnemonic, length, immediate] = instr_table[opcode];

        std::stringstream op_buf;
        char buf[64];


        for (unsigned off = 0; off < length; off++) {
            op_buf << std::hex << std::setw(2) << std::setfill('0') <<
                static_cast<unsigned>(debugContext.mmu.get().read_data(addr + off));
            op_buf << " "[off == length - 1];
        }

        if (immediate == 2) {
            const uint16_t imm = debugContext.mmu.get().read_data(addr + 1)
            | (debugContext.mmu.get().read_data(addr + 2) << 8);
            snprintf(buf, sizeof(buf), "%s 0x%04X", mnemonic.c_str(), imm);
        }
        else if (immediate == 1) {
            const uint8_t imm = debugContext.mmu.get().read_data(addr + 1);
            snprintf(buf, sizeof(buf), "%s 0x%02x", mnemonic.c_str(), imm);
        }
        else {
            snprintf(buf, sizeof(buf), "%s", mnemonic.c_str());
        }

        if (addr == getCurrentInstruction()) {
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "->0x%04X:", addr);
        }
        else if (breakpoints.count(addr)) {
            ImGui::TextColored(ImVec4(1, 0, 1, 1), "* 0x%04X:", addr);
        }
        else {
            ImGui::TextColored(ImVec4(1, 1, 1, 0.9), "0x%04X:", addr);
        }
        ImGui::SameLine(90.0f);
        ImGui::TextColored(ImVec4(1, 1, 1, 0.7), "%8s", op_buf.str().c_str());
        ImGui::SameLine(180.0f);
        ImGui::TextColored(ImVec4(1, 1, 1, 1), "%s", buf);

        addr += length;
    }
    ImGui::End();

}

void Debugger::stepIn() {
    emu_running = false;
    emu->run_one();
}

void Debugger::stepOut() {
    if (return_points.empty()) {
        stepOver();
    }
    else {
        emu->run_one();
        emu_running = true;
        checkStack = true;
        // do {
        //     emu->run_one();
        // } while (!breakpoints.count(this->getCurrentInstruction())
        //     && getCurrentInstruction() != return_points.top());
        // if (getCurrentInstruction() == return_points.top()) return_points.pop();
    }
}

void Debugger::stepOver() {
    const int currInst = debugContext.mmu.get().read_data(this->getCurrentInstruction());
    if (!instr_table[currInst].mnemonic.compare(0, 4, "CALL")) {
        const int nextInst = this->getNextInstruction();
        return_points.push(nextInst);
        stepOut();
        // if (!return_points.empty() && getCurrentInstruction() == return_points.top()) return_points.pop();
    }
    else {
        this->stepIn();
    }
}

void Debugger::runContinue() {
    emu_running = true;
}

void Debugger::toggleBreakpoint(const uint16_t address) {
    if (breakpoints.count(address)) breakpoints.erase(address);
    else this->breakpoints.insert(address);
}

void Debugger::inLoop() {
    unsigned t = this->instPerFrame;
    while (t--) {
        if (!return_points.empty() && getCurrentInstruction() == return_points.top()) {
            return_points.pop();
            if (checkStack) {
                running = false;
                checkStack = false;
                break;
            }
        }
        if (breakpoints.count(this->getCurrentInstruction())) {
            running = false;
            break;
        }
        emu->run_one();
    }
}

void Debugger::reload_rom() {
    this->emu = std::make_shared<Emulator>(romFilename);
    this->debugContext = emu->getDebugContext();
}

void Debugger::get_video_buffer(std::array<uint32_t, 160 * 144> &out_buffer) {
    std::lock_guard<std::mutex> lock(emu_mutex);
    out_buffer = emu->get_emu_video_buffer();
}

void Debugger::handle_input(sf::Keyboard::Key key, bool is_pressed) {
    auto state = emu->getJoyPad()->joypad_get_state();

    switch (key) {
        case sf::Keyboard::Key::Z:      state->b = is_pressed;      break; // B Button
        case sf::Keyboard::Key::X:      state->a = is_pressed;      break; // A Button
        case sf::Keyboard::Key::Enter:  state->start = is_pressed;  break; // Start
        case sf::Keyboard::Key::Tab:    state->select = is_pressed; break; // Select
        case sf::Keyboard::Key::Up:     state->up = is_pressed;     break; // D-Pad Up
        case sf::Keyboard::Key::Down:   state->down = is_pressed;   break; // D-Pad Down
        case sf::Keyboard::Key::Left:   state->left = is_pressed;   break; // D-Pad Left
        case sf::Keyboard::Key::Right:  state->right = is_pressed;  break; // D-Pad Right
        default: break;
    }
}

