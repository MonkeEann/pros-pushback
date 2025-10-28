#include "subsystems/conveyor.hpp"
#include "subsystems/subGlobals.hpp"
#include "roboConfig.hpp"

Conveyor::Conveyor(pros::Motor& backRollersMotor, pros::Motor& intakeMotor, pros::Motor& topRollerMotor, const double& speed)
    : backRollers(backRollersMotor), inMotor(intakeMotor), topRoller(topRollerMotor), spd(speed) {}

double Conveyor::getConveyorSpeed() const {return 127 * spd; }
void Conveyor::storeBlocks() {
    inMotor.move(getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
    topRoller.move(-getConveyorSpeed());
}
void Conveyor::scoreLow() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(-getConveyorSpeed() * .5);
}
void Conveyor::scoreMid() {
    inMotor.move(getConveyorSpeed() * .5);
    backRollers.move(-getConveyorSpeed() * .5);
    topRoller.move(-getConveyorSpeed());
}
void Conveyor::scoreHigh() {
    inMotor.move(getConveyorSpeed());
    backRollers.move(-getConveyorSpeed());
    topRoller.move(getConveyorSpeed());
}
void Conveyor::stopConveyor() {
    inMotor.move(0);
    backRollers.move(0);
    topRoller.move(0);
}
void Conveyor::matchLoad() {
    matchLoadPistonState = !matchLoadPistonState;
    matchLoadPiston.set_value(matchLoadPistonState);
}
void Conveyor::foldConveyor() {
    isConveyorUp = !isConveyorUp;
    foldPiston1.set_value(isConveyorUp);
    foldPiston2.set_value(isConveyorUp);
}