#include "debugger.hpp"

#include <functional>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics/Color.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

void Debugger::render() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags host_window_flags = 0;
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    host_window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::Begin("Main", nullptr , host_window_flags);

    render_disassembly_panel();
    render_tile_data_panel();
    render_command_prompt();
    render_registers_panel();
    render_hex_view();

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

void Debugger::render_hex_view() const {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    const float prompt_height = ImGui::GetTextLineHeightWithSpacing() + 20;
    const float panelHeight = main_size.y - 200.0f - prompt_height;
    constexpr float panelWidth = 320.0f;

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

void Debugger::render_registers_panel() const {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    constexpr float panelHeight = 200.0f;
    constexpr float panelWidth = 320.0f;

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

    ImGui::Begin("Registers", nullptr, window_flags);
    if (ImGui::BeginTable("RegSplit", 2, ImGuiTableFlags_None)) {

        renderReg("A", REG_TYPE::RT_A);
        renderReg("B", REG_TYPE::RT_B);
        renderReg("C", REG_TYPE::RT_C);
        renderReg("D", REG_TYPE::RT_D);


        renderReg("E", REG_TYPE::RT_E);
        renderReg("F", REG_TYPE::RT_F);
        renderReg("H", REG_TYPE::RT_H);
        renderReg("L", REG_TYPE::RT_L);

        renderReg("AF", REG_TYPE::RT_AF);
        renderReg("BC", REG_TYPE::RT_BC);
        renderReg("SP", REG_TYPE::RT_SP);

        renderReg("DE", REG_TYPE::RT_DE);
        renderReg("HL", REG_TYPE::RT_HL);
        renderReg("PC", REG_TYPE::RT_PC);

        ImGui::EndTable();
    }
    ImGui::End();
}

void Debugger::handle_command(char* commandBuffer) {

    std::string command(commandBuffer);

    const size_t first = command.find_first_not_of(" \t\n\r");
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
    else if (token == "h") {
        uint16_t addr; ss >> std::hex >> addr;
        this->hexview_curr_mem = addr;
    }
    else if (token == "speed") {
        unsigned speed; ss >> speed;
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
    if (running) {
        inLoop();
    }
    else if (ImGui::InputTextWithHint("##Prompt", "Enter command...", commandBuffer, sizeof(commandBuffer),
            ImGuiInputTextFlags_EnterReturnsTrue)) {
        handle_command(commandBuffer);
    }
    ImGui::SetKeyboardFocusHere(-1);
    ImGui::PopItemWidth();
    ImGui::End();
}

void Debugger::render_disassembly_panel() const {

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    constexpr float panel_width = 350.0f;
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
    return_points.push(getNextInstruction());
    emu->run_one();
    if (getCurrentInstruction() == return_points.top()) return_points.pop();
}

void Debugger::stepOut() {
    if (return_points.empty()) {
        stepOver();
    }
    else {
        emu->run_one();
        running = true;
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
    // do {
    //     emu->run_one();
    //     if (!return_points.empty() && getCurrentInstruction() == return_points.top()) return_points.pop();
    // } while (!breakpoints.count(this->getCurrentInstruction()));

    // if (!return_points.empty() && getCurrentInstruction() == return_points.top()) return_points.pop();

    emu->run_one();
    running = true;
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