#include "classDefine.hpp"
#include "roboConfig.hpp"

Odom monkeOdom(WHEEL_DIAMETER, SIDEWAYS_ODOM_OFFSET, FORWARD_ODOM_OFFSET);
Drivetrain monkeDrivetrain(leftDrivetrain, rightDrivetrain);
Conveyor monkeConveyor(backRollersMotor, intakeMotor, hoardMotor, topRollerMotor, CONVEYOR_SPEED);

PID drivePID(DRIVE_PID_KP, DRIVE_PID_KI, DRIVE_PID_KD);
PID PID1(PID_1_KP, PID_1_KI, PID_1_KD);
PID PID2(PID_2_KP, PID_2_KI, PID_2_KD);