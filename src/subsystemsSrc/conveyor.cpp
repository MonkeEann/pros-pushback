#include "subsystems/conveyor.hpp"

Conveyor::Conveyor(pros::Motor& backRollersMotor, pros::Motor& intakeMotor, pros::Motor& hoardMotor, pros::Motor& topRollerMotor, const double& speed)
    : backRollers(backRollersMotor), inMotor(intakeMotor), hrdMotor(hoardMotor), topRoller(topRollerMotor), spd(speed) {}

double Conveyor::getConveyorSpeed() const {return 127 * spd; }
void Conveyor::storeBlocks() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
    topRoller.move(getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed());
    hoodPistonState = false;
    hoodPiston.set_value(hoodPistonState);
}
void Conveyor::scoreLow() {
    inMotor.move(getConveyorSpeed());
    backRollers.move(-getConveyorSpeed());
    topRoller.move(-getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed());
    hoodPistonState = true;
    hoodPiston.set_value(hoodPistonState);
}
void Conveyor::scoreMid() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
    topRoller.move(-getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed()); // Adjust speed for mid scoring
    hoodPistonState = true;
    hoodPiston.set_value(hoodPistonState);
}
void Conveyor::scoreHigh() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
    topRoller.move(getConveyorSpeed());
    hrdMotor.move(getConveyorSpeed());
    hoodPistonState = true;
    hoodPiston.set_value(hoodPistonState);
}
void Conveyor::stopConveyor() {
    inMotor.move(0);
    backRollers.move(0);
    topRoller.move(0);
    hrdMotor.move(0);
    hoodPistonState = false;
    hoodPiston.set_value(hoodPistonState);
}
void Conveyor::matchLoad() {
    matchLoadPistonState = !matchLoadPistonState;
    matchLoadPiston.set_value(matchLoadPistonState);
}