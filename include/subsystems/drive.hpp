#ifndef DRIVE_HPP
#define DRIVE_HPP

class Drivetrain {
    private: 

        pros::MotorGroup leftDrivetrain;
        pros::MotorGroup rightDrivetrain;
    public:
        Drivetrain();

        void teleopControl();
        void driveWithAutoAlign();
        void setSpeed(double leftSpeed, double rightSpeed);
        void stop();

};

#endif
