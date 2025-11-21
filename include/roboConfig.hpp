#ifndef ROBOCONFIG_HPP
#define ROBOCONFIG_HPP

#include <cstdint>
#include "pros/misc.h"
//Button configuration
constexpr pros::controller_digital_e_t SCORE_LOW_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
constexpr pros::controller_digital_e_t SCORE_MID_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;
constexpr pros::controller_digital_e_t SCORE_HIGH_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
constexpr pros::controller_digital_e_t STORE_BUTTON = pros::E_CONTROLLER_DIGITAL_L2;
constexpr pros::controller_digital_e_t MATCH_LOAD_BUTTON = pros::E_CONTROLLER_DIGITAL_X;
constexpr pros::controller_digital_e_t FOLD_BUTTON = pros::E_CONTROLLER_DIGITAL_A;
constexpr pros::controller_digital_e_t AUTO_BUTTON = pros::E_CONTROLLER_DIGITAL_DOWN;
constexpr pros::controller_digital_e_t TEST_BUTTON = pros::E_CONTROLLER_DIGITAL_LEFT;


// Boolean flags for robot configuration
constexpr bool LIVE_TUNING = false;
constexpr bool UI_TEST_MODE = false; 
constexpr bool AUTON_ENABLED = true; 

extern bool isConveyorUp;

// PID constants for various subsystems
extern double ANGULAR_PID_KP;
extern double ANGULAR_PID_KI;
extern double ANGULAR_PID_KD;

extern double PID_1_KP;
extern double PID_1_KI;
extern double PID_1_KD;

extern double PID_2_KP;
extern double PID_2_KI;
extern double PID_2_KD;

// Declare external subsystem objects

// Motor port declarations
constexpr std::int8_t LEFT_DRIVETRAIN_PORTS[3] = {1, -2, -3}; 
constexpr std::int8_t RIGHT_DRIVETRAIN_PORTS[3] = {8, -9, 10}; 

constexpr int INTAKE_MOTOR_PORT = 4;
constexpr int BACK_ROLLERS_PORT = 5;
constexpr int TOP_ROLLER_PORT = -6;

// Test Port
// We will define a test port for testing purposes, this can be used to test individual motors.
constexpr int TEST_PORT = 20;

constexpr char FOLD_PISTON_1_PORT = 'B';
constexpr char FOLD_PISTON_2_PORT = 'C';
constexpr char MATCH_LOAD_PORT = 'D';

// Subsystem Settings

constexpr double DRIVETRAIN_SPEED = 1.0; // Full speed for the drivetrain
constexpr double JOYSTICK_DEADBAND = 3; // Deadband for joystick inputs
constexpr double DRIVETRAIN_DEADBAND = 10; // Deadband for drivetrain movement
constexpr double CONVEYOR_SPEED = 1.0; // Speed for the intake conveyor
constexpr double INTAKE_SPEED = 1.0; // Speed for the intake motor


constexpr double WHEEL_DIAMETER = 3.25;
constexpr double SIDEWAYS_ODOM_OFFSET = 2;
constexpr double FORWARD_ODOM_OFFSET = 2;

#endif  // ROBOCONFIG_HPP