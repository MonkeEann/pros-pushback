#include "roboConfig.hpp"

/* In this file we will define subsystems and configure attributes to help with testing later on (e.g. subsystem speeds)
 * The main purpose of this file is to make troubleshooting as easy as possible by having all configurations in one place.
 * To do so we will have variables for each motors port and subsystem speeds.
 */

// BUTTON CONFIGURATION
bool isConveyorUp = false;

double ANGULAR_PID_KP = 6.0;
double ANGULAR_PID_KI = 0.0;
double ANGULAR_PID_KD = 36.0;

double PID_1_KP = 0.0;
double PID_1_KI = 0.0;
double PID_1_KD = 0.0;

double PID_2_KP = 0.0;
double PID_2_KI = 0.0;
double PID_2_KD = 0.0;


