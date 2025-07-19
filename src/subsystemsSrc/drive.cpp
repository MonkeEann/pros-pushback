#include "subsystems/drive.hpp"

Drivetrain::Drivetrain (pros::MotorGroup& leftMotors, pros::MotorGroup& rightMotors)
    : leftDrMotors(leftMotors), rightDrMotors(rightMotors) {};

void Drivetrain::teleopControl() {

    int forwardSpeed = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turnSpeed = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    double leftSpeed = forwardSpeed + turnSpeed;
    double rightSpeed = forwardSpeed - turnSpeed;

    setSpeed(leftSpeed, rightSpeed);
}
void Drivetrain::setSpeed(double leftSpeed, double rightSpeed) {
    leftDrMotors.move(leftSpeed);
    rightDrMotors.move(rightSpeed);
}
void Drivetrain::stop() {
    leftDrMotors.move(0);
    rightDrMotors.move(0);
}
  