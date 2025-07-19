#include "subsystems/conveyor.hpp"

Conveyor::Conveyor(pros::Motor& bottomMotor, pros::Motor& intakeMotor, pros::Motor& hoardMotor, pros::Motor& backConveyorMotors)
    : btmMotor(bottomMotor), inMotor(intakeMotor), hrdMotor(hoardMotor), backConveyor(backConveyorMotors) {};

void Conveyor::storeBlocksLow() {
    inMotor.move(-127);
    btmMotor.move(127);
    backConveyor.move(-127);
    hrdMotor.move(-127);
}
void Conveyor::scoreLow() {
    inMotor.move(127);
    btmMotor.move(127);
    backConveyor.move(-127);
    hrdMotor.move(127);
}
void Conveyor::scoreMid() {

}
void Conveyor::scoreHigh() {

}
void Conveyor::stopConveyor() {
    inMotor.move(0);
    btmMotor.move(0);
    backConveyor.move(0);
    hrdMotor.move(0);
}