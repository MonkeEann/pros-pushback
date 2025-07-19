#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include "subsystems/subGlobals.hpp"
class Conveyor {
private:
// Private members for conveyor control can be added here
    pros::Motor& btmMotor;
    pros::Motor& inMotor;
    pros::Motor& hrdMotor;
    pros::Motor& backConveyor;

public:
    Conveyor(pros::Motor& bottomMotor, pros::Motor& intakeMotor, pros::Motor& hoardMotor, pros::Motor& backConveyorMotors);

    void storeBlocksLow();
    void scoreLow();
    void scoreMid();
    void scoreHigh();
    void stopConveyor();

};

#endif // CONVEYOR_HPP