#ifndef CLASS_DEFINE_HPP
#define CLASS_DEFINE_HPP
#include "auton/autoGlobals.hpp"
#include "subsystems/conveyor.hpp"
#include "utils/PID.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep

extern PID angularPID;
extern PID lateralPID;
extern PID PID2;
extern Conveyor monkeConveyor;
extern autonManager autonMgr;

#endif // CLASS_DEFINE_HPP