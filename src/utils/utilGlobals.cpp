#include "UI/uiGlobals.hpp"
#include "utils/utilGlobals.hpp"
#include "classDefine.hpp"
#include "subsystems/subGlobals.hpp"
#include "roboConfig.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include <cstdio>
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

void debugTaskFn(void* param){

    while (true) {
        auto pose = monkeChassis.getPose();
        master.print(0, 0, "X: %.2f Y: %.2f Theta: %.2f",
                    pose.x,
                    pose.y,
                    pose.theta);
        getBattery();

        pros::delay(5000);
    }
    
}


void initRobot(){
    initializeGUI();
    //Check Flags
    if (UI_TEST_MODE)
    {
        printf("UI TEST MODE: Skipping IMU Calibration\n");
    } else {
        printf("Normal Mode: Calibrating\n");
        monkeChassis.calibrate();
        monkeChassis.setPose(44.5, 0, 270);
        monkeConveyor.foldConveyor();
    }
    if (LIVE_TUNING)
    {
        printf("LIVE TUNING ENABLED: Starting GUI Tuning Task\n");
    } else {
        printf("LIVE TUNING DISABLED\n");
    }
    if (AUTON_ENABLED)
    {
        // Print out Selected Auton
        printf("AUTON ENABLED | Selected Auton: %s\n", autonMgr.getSelectedAutonName().c_str());
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "Selected Auton: %s", autonMgr.getSelectedAutonName().c_str());
        printToTerminal(1, buffer);
    } else {
        printf("AUTON DISABLED\n");
        printToTerminal(1,"AUTON DISABLED");
    }
	pros::Task debugTask(debugTaskFn, nullptr, "Debug Task");

}