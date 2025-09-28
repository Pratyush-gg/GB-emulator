//
// Created by shawn on 25-09-2025.
//

#include "debugger.hpp"

#include <iomanip>
#include <sstream>

#include "imgui.h"

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
    render_command_prompt();
    render_registers_panel();
    render_hex_view();

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
        ImGui::TextColored(ImVec4(1, 0, 0, 1), currLine.str().c_str());

        currLine.clear();
        currLine.str("");

        ImGui::SameLine(70.0f);

        for (unsigned loc = 0; loc < hexview_num_cols; loc++) {
            currLine << std::hex << std::uppercase << std::setw(2) << static_cast<unsigned>(debugContext.mmu.get().read_data(curr_addr)) << "  ";
            curr_addr++;
        }
        ImGui::TextColored(ImVec4(0, 1, 1, 1), currLine.str().c_str());
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
    const auto panel_size = ImVec2(panelWidth, panelHeight);

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

        renderReg("AF", REG_TYPE::RT_AF);
        renderReg("BC", REG_TYPE::RT_BC);
        renderReg("SP", REG_TYPE::RT_SP);

        renderReg("E", REG_TYPE::RT_E);
        renderReg("F", REG_TYPE::RT_F);
        renderReg("H", REG_TYPE::RT_H);
        renderReg("L", REG_TYPE::RT_L);

        renderReg("DE", REG_TYPE::RT_DE);
        renderReg("HL", REG_TYPE::RT_HL);
        renderReg("PC", REG_TYPE::RT_PC);

        ImGui::EndTable();
    }
    ImGui::End();
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
    if (ImGui::InputTextWithHint("##Prompt", "Enter command...", commandBuffer, sizeof(commandBuffer),
            ImGuiInputTextFlags_EnterReturnsTrue)) {
        if (strcmp(commandBuffer, "s") == 0) {
            this->stepIn();
        }
        else if (strcmp(commandBuffer, "n") == 0) {
            this->stepOver();
        }
        else if (strcmp(commandBuffer, "f") == 0) {
            if (!return_points.empty()) {
                this->stepOut();
            }
        }
        else if (strcmp(commandBuffer, "c") == 0) {
            this->runContinue();
        }
        else if (strncmp(commandBuffer, "b ", 2) == 0) {
            uint16_t temp_addr;
            if (sscanf(commandBuffer, "b %hx", &temp_addr) == 1) {
                this->toggleBreakpoint(temp_addr);
            }
        }
        else if (strncmp(commandBuffer, "h ", 2) == 0) {
            uint16_t temp_addr;
            if (sscanf(commandBuffer, "h %hx", &temp_addr) == 1) {
                this->hexview_curr_mem = temp_addr;
            }
        }
        strcpy(commandBuffer, "");
        ImGui::SetKeyboardFocusHere(-1);
    }
    ImGui::PopItemWidth();
    ImGui::End();
}

void Debugger::render_disassembly_panel() const {

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 main_pos = viewport->WorkPos;
    const ImVec2 main_size = viewport->WorkSize;

    constexpr float panel_width = 250.0f;
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

        char buf[64];

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
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "->%04X:\t%s", addr, buf);
        }
        else if (breakpoints.count(addr)) {
            ImGui::TextColored(ImVec4(1, 0, 1, 1), "* %04X:\t%s", addr, buf);
        }
        else {
            ImGui::Text("%04X:\t%s", addr, buf);
        }
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
        do {
            emu->run_one();
        } while (!breakpoints.count(this->getCurrentInstruction())
            && getCurrentInstruction() != return_points.top());
        if (getCurrentInstruction() == return_points.top()) return_points.pop();
    }
}

void Debugger::stepOver() {
    const int currInst = debugContext.mmu.get().read_data(this->getCurrentInstruction());
    if (!instr_table[currInst].mnemonic.compare(0, 4, "CALL")) {
        const int nextInst = this->getNextInstruction();
        return_points.push(nextInst);
        stepOut();
        if (!return_points.empty() && getCurrentInstruction() == return_points.top()) return_points.pop();
    }
    else {
        this->stepIn();
    }
}

void Debugger::runContinue() {
    do {
        if (!return_points.empty() && getCurrentInstruction() == return_points.top()) return_points.pop();
        emu->run_one();
    } while (!breakpoints.count(this->getCurrentInstruction()));

    if (!return_points.empty() && getCurrentInstruction() == return_points.top()) return_points.pop();
}

void Debugger::toggleBreakpoint(const uint16_t address) {
    if (breakpoints.count(address)) breakpoints.erase(address);
    else this->breakpoints.insert(address);
}
