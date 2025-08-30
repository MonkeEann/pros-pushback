#ifndef ROBOCONFIG_HPP
#define ROBOCONFIG_HPP

#include <cstdint>
#include "pros/misc.h"
//Button configuration
constexpr pros::controller_digital_e_t SCORE_LOW_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
constexpr pros::controller_digital_e_t SCORE_MID_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;
constexpr pros::controller_digital_e_t SCORE_HIGH_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
constexpr pros::controller_digital_e_t TEST_BUTTON = pros::E_CONTROLLER_DIGITAL_A;

// Boolean flags for robot configuration
constexpr bool ODOM_STATUS = false;
constexpr bool LIVE_TUNING = true;

// PID constants for various subsystems
extern double DRIVE_PID_KP;
extern double DRIVE_PID_KI;
extern double DRIVE_PID_KD;

extern double PID_1_KP;
extern double PID_1_KI;
extern double PID_1_KD;

extern double PID_2_KP;
extern double PID_2_KI;
extern double PID_2_KD;

// Declare external subsystem objects

// Motor port declarations
constexpr std::int8_t LEFT_DRIVETRAIN_PORTS[3] = {11, 12, 13}; 
constexpr std::int8_t RIGHT_DRIVETRAIN_PORTS[3] = {-18, -19, -20}; 

constexpr int INTAKE_MOTOR_PORT = 4;
constexpr int BACK_ROLLERS_PORT = 5;
constexpr int HOARD_MOTOR_PORT = 7;
constexpr int TOP_ROLLER_PORT = 6;

// Test Port
// We will define a test port for testing purposes, this can be used to test individual motors.
constexpr int TEST_PORT = 20;

// Subsystem Speeds

constexpr double DRIVETRAIN_SPEED = 1.0; // Full speed for the drivetrain
constexpr double CONVEYOR_SPEED = 0.8; // Speed for the intake conveyor
constexpr double INTAKE_SPEED = 1.0; // Speed for the intake motor


constexpr double WHEEL_DIAMETER = 3.25;
constexpr double SIDEWAYS_ODOM_OFFSET = 2;
constexpr double FORWARD_ODOM_OFFSET = 2;

#endif  // ROBOCONFIG_HPP