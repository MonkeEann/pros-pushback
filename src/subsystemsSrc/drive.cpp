#include "main.h"

Drivetrain::Drivetrain ()
: leftDrivetrain({1, 2, 3}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees),
  rightDrivetrain({-8, -9, -10}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees) {
    // Constructor initializes left and right motor groups
}

void Drivetrain::teleopControl() {
    int forwardSpeed = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turnSpeed = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    double leftSpeed = forwardSpeed + turnSpeed;
    double rightSpeed = forwardSpeed - turnSpeed;

    setSpeed(leftSpeed, rightSpeed);
}
void Drivetrain::setSpeed(double leftSpeed, double rightSpeed) {
    leftDrivetrain.move(leftSpeed);
    rightDrivetrain.move(rightSpeed);
}
void Drivetrain::stop() {
    leftDrivetrain.move(0);
    rightDrivetrain.move(0);
}
    