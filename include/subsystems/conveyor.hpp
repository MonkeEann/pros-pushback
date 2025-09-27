#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include "subsystems/subGlobals.hpp"
class Conveyor {
private:
// Private members for conveyor control can be added here
    pros::Motor& backRollers;
    pros::Motor& inMotor;
    pros::Motor& hrdMotor;
    pros::Motor& topRoller;

    
    // Default speed for the conveyor, can be adjusted based on the configuration
    // This speed is a multiplier for the motor speed, ranging from 0 to 1
    // For example, 0.8 means the conveyor will run at 80% of its maximum speed
    // Forward speed is positive, backward speed is negative
    double spd;
    bool hoodPistonState = false;
    bool matchLoadPistonState = false;

public:
    Conveyor(pros::Motor& backRollersMotor, pros::Motor& intakeMotor, pros::Motor& hoardMotor, pros::Motor& topRollerMotor, const double& speed);

    double getConveyorSpeed() const;
    void storeBlocks();
    void scoreLow();
    void scoreMid();
    void scoreHigh();
    void stopConveyor();
    void matchLoad();
    void hoodPistonManual();

};

#endif // CONVEYOR_HPP