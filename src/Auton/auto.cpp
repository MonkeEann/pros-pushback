#include "classDefine.hpp"
#include "subsystems/subGlobals.hpp"
#include "auton/auto.hpp"

ASSET(BlueCenterLongPath2_txt);

void runAuto(autonRoutine routine){
    switch(routine){
        case autonRoutine::SKILLS:
            // Run skills auton
            break;
        case autonRoutine::BLUE_LEFT:
            // Run left side auton
            monkeChassis.moveToPose(23.4, -22.6, 90, 4000);       

            break;
        case autonRoutine::BLUE_RIGHT:
            // Run right side auton
                    // Test function can be added here
        // Working Auton Code
        // Intake blocks
        monkeChassis.moveToPose(25, 31, 315, 4000, {.maxSpeed = 127*0.6}, false);
        monkeConveyor.storeBlocks();
        // Move to center high goal
        monkeChassis.moveToPose(10, 14, 315, 4000, {.maxSpeed = 127*0.6}, false);
        monkeConveyor.stopConveyor();
        // Move to matchloader
        monkeChassis.moveToPose(30,34, 315, 1000, {.forwards = false, .maxSpeed = 127*0.6, .earlyExitRange = 8});
        monkeChassis.moveToPose(50,48, 270, 4000, {.forwards = false, .maxSpeed = 127*0.6});
        monkeChassis.turnToHeading(90, 4000);
        //Move Into Loader
        monkeChassis.moveToPose(55,48, 270, 4000, {.forwards = false, .maxSpeed = 127*0.6});

        //Test Auton 
        // Score on long goal
        monkeChassis.moveToPose(50,48, 270, 4000, {.forwards = false, .maxSpeed = 127*0.6});
        monkeChassis.moveToPose(33,45, 90, 4000, {.forwards = false, .maxSpeed = 127*0.6});
            break;
        case autonRoutine::RED_LEFT:
            // Run left side auton
            break;
        case autonRoutine::RED_RIGHT:
            // Run right side auton
            break;
        case autonRoutine::NONE:
            // Do nothing
            break;
        default:
            // Do nothing
            break;
    }
}
