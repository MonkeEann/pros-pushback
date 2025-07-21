#include "utils/terminalFunc.hpp"
#include "UI/uiGlobals.hpp"
#include "utils/utilGlobals.hpp"
#include <string>
#include <sstream>
#include <vector>

void printToTerminal(int lineIndex, const char* message){
    if (!terminalTextArea) return;    

    const char* currentText = lv_textarea_get_text(terminalTextArea);
    std::string text(currentText);

    // Split the text into lines
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;

    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    if (lineIndex < 0) return;

    if ((size_t)lineIndex < lines.size()){
        lines[lineIndex] = message;
    } else {
        while((int)lines.size() < lineIndex){
            lines.push_back("");
        }
        lines.push_back(message);
    }

    std::string newText;
    for (const auto& l : lines) {
        newText += l + "\n";
    }

    lv_textarea_set_text(terminalTextArea, newText.c_str());
    lv_textarea_set_cursor_pos(terminalTextArea, LV_TEXTAREA_CURSOR_LAST);
}

void deleteLines(int startLine, int endLine){
    if(!terminalTextArea) return;

    if (startLine < 0 || endLine < startLine) return;

    const char* currentText = lv_textarea_get_text(terminalTextArea);

    std::string text(currentText);
    // Split the full text into individual lines
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    lines.erase(lines.begin() + startLine, lines.begin() + endLine + 1);

    std::string newText;
    for (const auto& l : lines) {
        newText += l + "\n";
    }

    lv_textarea_set_text(terminalTextArea, newText.c_str());
    lv_textarea_set_cursor_pos(terminalTextArea, LV_TEXTAREA_CURSOR_LAST);

}


