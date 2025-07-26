#include "UI/uiGlobals.hpp"
#include "utils/utilGlobals.hpp"
#include "pros/rtos.hpp"
#include <string>
#include <sstream>
#include <vector>

pros::Task* printBattery = nullptr;

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

void getBattery(){
    int capacity = pros::battery::get_capacity();
    
    char buffer[100];

    if (capacity >= 75) {
        snprintf(buffer, sizeof(buffer), "BATTERY LEVEL: %d%% - GOOD TO COMPETE", capacity);
    } else if (capacity >= 25 && capacity < 75){
        snprintf(buffer, sizeof(buffer), "BATTERY LEVEL: %d%% - REPLACE FOR MATCH", capacity);
    } else {
        snprintf(buffer, sizeof(buffer), "BATTERY LEVEL: %d%% - CHARGE BATTERY", capacity);
    }

    printToTerminal(0, buffer);
}

void batteryTaskFn(void* param) {
    while (true) {
        getBattery();
        pros::delay(1000); 
    }
}
void debugTaskFn(void* param){

    while (true) {
        printf("Task: %s Priority: %d\n",
            lvglTask->get_name(),
            lvglTask->get_priority()
        );
        printf("Task: %s Priority: %d\n",
            printBattery->get_name(),
            printBattery->get_priority()
        );
        pros::delay(5000);
    }
    
}

