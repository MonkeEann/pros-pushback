#include "classDefine.hpp"
#include "roboConfig.hpp"


PID angularPID(ANGULAR_PID_KP, ANGULAR_PID_KI, ANGULAR_PID_KD);
PID lateralPID(PID_1_KP, PID_1_KI, PID_1_KD);
PID PID2(PID_2_KP, PID_2_KI, PID_2_KD);
autonManager autonMgr;