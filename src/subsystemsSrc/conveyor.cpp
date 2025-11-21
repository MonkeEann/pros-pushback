#include "subsystems/conveyor.hpp"
#include "subsystems/subGlobals.hpp"
#include "roboConfig.hpp"

Conveyor::Conveyor(pros::Motor& backRollersMotor, pros::Motor& intakeMotor, pros::Motor& topRollerMotor, const double& speed)
    : backRollers(backRollersMotor), inMotor(intakeMotor), topRoller(topRollerMotor), spd(speed) {}

double Conveyor::getConveyorSpeed() const {return 127 * spd; }
void Conveyor::storeBlocks() {
    inMotor.move(getConveyorSpeed() * .75);
    backRollers.move(-getConveyorSpeed());
    topRoller.move(-getConveyorSpeed());
}
void Conveyor::scoreLow() {
    inMotor.move(-getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
}
void Conveyor::scoreMid() {
    inMotor.move(getConveyorSpeed() * .5);
    backRollers.move(getConveyorSpeed());
    topRoller.move(-getConveyorSpeed() * .25);
}
void Conveyor::scoreMid(double speed) {
    inMotor.move(getConveyorSpeed() * (speed / 100));
    backRollers.move(getConveyorSpeed() * (speed / 100));
    topRoller.move(-getConveyorSpeed() * (speed / 100) * .5);
}
void Conveyor::scoreHigh() {
    inMotor.move(getConveyorSpeed());
    backRollers.move(getConveyorSpeed());
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