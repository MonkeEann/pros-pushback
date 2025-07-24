#include "classDefine.hpp"
#include "roboConfig.hpp"

Odom monkeOdom(WHEEL_DIAMETER, SIDEWAYS_ODOM_OFFSET, FORWARD_ODOM_OFFSET);
Drivetrain monkeDrivetrain(leftDrivetrain, rightDrivetrain);
Conveyor monkeConveyor(backRollersMotor, intakeMotor, hoardMotor, topRollerMotor, CONVEYOR_SPEED);
