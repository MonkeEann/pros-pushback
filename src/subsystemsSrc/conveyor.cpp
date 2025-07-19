#include "subsystems/conveyor.hpp"

Conveyor::Conveyor(pros::Motor& backRollersMotor, pros::Motor& intakeMotor, pros::Motor& hoardMotor, pros::Motor& topRollerMotor)
    : backRollers(backRollersMotor), inMotor(intakeMotor), hrdMotor(hoardMotor), topRoller(topRollerMotor) {};

void Conveyor::storeBlocksLow() {
    inMotor.move(-conveyorSpeed);
    backRollers.move(-conveyorSpeed);
    topRoller.move(-conveyorSpeed);
    hrdMotor.move(-conveyorSpeed);
}
void Conveyor::scoreLow() {
    inMotor.move(conveyorSpeed);
    backRollers.move(-conveyorSpeed);
    topRoller.move(-conveyorSpeed);
    hrdMotor.move(conveyorSpeed);
}
void Conveyor::scoreMid() {

}
void Conveyor::scoreHigh() {

}
void Conveyor::stopConveyor() {
    inMotor.move(0);
    backRollers.move(0);
    topRoller.move(0);
    hrdMotor.move(0);
}