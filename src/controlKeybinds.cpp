#include "pros/misc.h"
#include "subsystems/subGlobals.hpp"
#include "classDefine.hpp"
#include "roboConfig.hpp"

void updateControlKeybinds() {
    int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    monkeChassis.curvature(leftY, rightX);

    // CONVEYOR CONTROLS
    if(master.get_digital(SCORE_LOW_BUTTON)){
        monkeConveyor.scoreLow();

    } else if (master.get_digital(SCORE_MID_BUTTON)){
        monkeConveyor.scoreMid();

    } else if (master.get_digital(SCORE_HIGH_BUTTON)){
        monkeConveyor.scoreHigh();

    } else if (master.get_digital(STORE_BUTTON)){
        monkeConveyor.storeBlocks();

    } else if (master.get_digital_new_press(MATCH_LOAD_BUTTON)){
        monkeConveyor.matchLoad();

    } else if (master.get_digital_new_press(FOLD_BUTTON)){
        monkeConveyor.foldConveyor();

    } else if(master.get_digital_new_press(DESCORE_BUTTON)){
        static bool descoreState = false;
        descoreState = !descoreState;
        descorePiston.set_value(descoreState);
    }else if(!monkeChassis.isInMotion() && master.get_digital_new_press(AUTO_BUTTON)){
        autonMgr.runSelectedAuton();

    } else if (master.get_digital_new_press(TEST_BUTTON)){
        //* Test function can be added here

    } else{
        monkeConveyor.stopConveyor();
    }
}