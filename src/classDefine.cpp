#include "classDefine.hpp"
#include "roboConfig.hpp"

Drivetrain monkeDrivetrain(leftDrivetrain, rightDrivetrain);
Conveyor monkeConveyor(backRollersMotor, intakeMotor, hoardMotor, topRollerMotor, CONVEYOR_SPEED);