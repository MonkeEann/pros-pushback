#ifndef CLASS_DEFINE_HPP
#define CLASS_DEFINE_HPP

#include "subsystems/conveyor.hpp"
#include "subsystems/drive.hpp"
#include "utils/Odom.hpp"
#include "utils/PID.hpp"

extern Odom monkeOdom;
extern PID drivePID;
extern PID PID1;
extern PID PID2;
extern Drivetrain monkeDrivetrain;
extern Conveyor monkeConveyor;

#endif //CLASS_DEFINE_HPP