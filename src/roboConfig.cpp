#include "roboConfig.hpp"

/* In this file we will define subsystems and configure attributes to help with testing later on (e.g. subsystem speeds)
 * The main purpose of this file is to make troubleshooting as easy as possible by having all configurations in one place.
 * To do so we will have variables for each motors port and subsystem speeds.
 */

// Motor Ports
const std::int8_t LEFT_DRIVETRAIN_PORTS[3] = {1, 2, 3}; 
const std::int8_t RIGHT_DRIVETRAIN_PORTS[3] = {-8, -9, -10}; 

const int INTAKE_MOTOR_PORT = 4;
const int BACK_ROLLERS_PORT = 5;
const int HOARD_MOTOR_PORT = 6;
const int TOP_ROLLER_PORT = 7;

// Test Port
// We will define a test port for testing purposes, this can be used to test individual motors.
const int TEST_PORT = 20;

// Subsystem Speeds

const double DRIVETRAIN_SPEED = 1.0; // Full speed for the drivetrain
const double CONVEYOR_SPEED = 0.8; // Speed for the intake conveyor
const double INTAKE_SPEED = 1.0; // Speed for the intake motor

const bool ODOM_STATUS = false;
const double WHEEL_DIAMETER = 3.25;
const double SIDEWAYS_ODOM_OFFSET = 2;
const double FORWARD_ODOM_OFFSET = 2;

