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
            intakeTask(nullptr);
            monkeChassis.moveToPose(20, 15, 90, 4000);       

            break;
        case autonRoutine::BLUE_RIGHT:
            // Run right side auton
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
