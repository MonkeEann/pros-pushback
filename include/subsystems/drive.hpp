#ifndef DRIVE_HPP
#define DRIVE_HPP

#include "subsystems/subGlobals.hpp"
class Drivetrain {
private: 
    pros::MotorGroup& leftDrMotors;
    pros::MotorGroup& rightDrMotors;
public:
    Drivetrain(pros::MotorGroup& leftMotors, pros::MotorGroup& rightMotors);

    void teleopControl();
    void driveWithAutoAlign();
    void setSpeed(double leftSpeed, double rightSpeed);
    void stop();

};

#endif // DRIVE_HPP
