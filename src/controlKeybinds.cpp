#include "pros/misc.h"
#include "subsystems/subGlobals.hpp"
#include "classDefine.hpp"
#include "roboConfig.hpp"

void updateControlKeybinds() {
    //Test Port
    if(master.get_digital(TEST_BUTTON)){
        testMotor.move(127);
    } else {
        testMotor.move(0);
    }

    // CONVEYOR CONTROLS
    if(master.get_digital(SCORE_LOW_BUTTON)){
        monkeConveyor.scoreLow();
    } else if (master.get_digital(SCORE_MID_BUTTON)){
        monkeConveyor.scoreMid();
    } else if (master.get_digital(SCORE_HIGH_BUTTON)){
        monkeConveyor.scoreHigh();
    } else {
        monkeConveyor.stopConveyor();
    }
}