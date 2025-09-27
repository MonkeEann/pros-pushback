#include "subsystems/conveyor.hpp"

Conveyor::Conveyor(pros::Motor& backRollersMotor, pros::Motor& intakeMotor, pros::Motor& hoardMotor, pros::Motor& topRollerMotor, const double& speed)
    : backRollers(backRollersMotor), inMotor(intakeMotor), hrdMotor(hoardMotor), topRoller(topRollerMotor), spd(speed) {}

double Conveyor::getConveyorSpeed() const {return 127 * spd; }
void Conveyor::storeBlocks() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(-getConveyorSpeed());
    topRoller.move(getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed());
}
void Conveyor::scoreLow() {
    inMotor.move(getConveyorSpeed());
    backRollers.move(-getConveyorSpeed() * .5);
    topRoller.move(-getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed());
}
void Conveyor::scoreMid() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
    topRoller.move(-getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed()); // Adjust speed for mid scoring
}
void Conveyor::scoreHigh() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
    topRoller.move(getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed());
}
void Conveyor::stopConveyor() {
    inMotor.move(0);
    backRollers.move(0);
    topRoller.move(0);
    hrdMotor.move(0);
}
void Conveyor::matchLoad() {
    matchLoadPistonState = !matchLoadPistonState;
    matchLoadPiston.set_value(matchLoadPistonState);
}
void Conveyor::hoodPistonManual() {
    hoodPistonState = !hoodPistonState;
    hoodPiston.set_value(hoodPistonState);
}