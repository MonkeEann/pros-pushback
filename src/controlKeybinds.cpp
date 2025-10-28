#include "pros/misc.h"
#include "subsystems/subGlobals.hpp"
#include "classDefine.hpp"
#include "roboConfig.hpp"
#include "auton/auto.hpp"

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

    } else if(!monkeChassis.isInMotion() && master.get_digital_new_press(AUTO_BUTTON)){
        runAuto(autonRoutine::BLUE_LEFT);

    } else if (master.get_digital_new_press(TEST_BUTTON)){
        // Test function can be added here
        // Working Auton Code
        // Intake blocks
        monkeChassis.moveToPose(25, -31, 315, 4000, {.maxSpeed = 127*0.6}, false);
        monkeConveyor.storeBlocks();
        // Move to center high goal
        monkeChassis.moveToPose(10, -14, 315, 4000, {.maxSpeed = 127*0.6}, false);
        monkeConveyor.stopConveyor();
        // Move to matchloader
        monkeChassis.moveToPose(30,-34, 315, 1000, {.forwards = false, .maxSpeed = 127*0.6, .earlyExitRange = 8});
        monkeChassis.moveToPose(50,-48, 270, 4000, {.forwards = false, .maxSpeed = 127*0.6});
        monkeChassis.turnToHeading(90, 4000);
        //Move Into Loader
        monkeChassis.moveToPose(55,-48, 270, 4000, {.forwards = false, .maxSpeed = 127*0.6});

        //Test Auton 
        // Score on long goal
        monkeChassis.moveToPose(50,-48, 270, 4000, {.forwards = false, .maxSpeed = 127*0.6});
        monkeChassis.moveToPose(33,-45, 90, 4000, {.forwards = false, .maxSpeed = 127*0.6});


    } else{
        monkeConveyor.stopConveyor();
    }
}