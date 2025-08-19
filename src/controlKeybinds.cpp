#include "UI/uiGlobals.hpp"
#include "subsystems/subGlobals.hpp"
#include "utils/utilGlobals.hpp"

void updateControlKeybinds() {
    // CONVEYOR CONTROLS
    if(master.get_digital(DIGITAL_R1)){
        monkeConveyor.scoreLow();
    } else if (master.get_digital(DIGITAL_R2)){
        monkeConveyor.scoreMid();
    } else if (master.get_digital(DIGITAL_L1)){
        monkeConveyor.scoreHigh();
    }
}