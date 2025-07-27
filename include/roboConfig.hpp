#ifndef ROBOCONFIG_HPP
#define ROBOCONFIG_HPP

#include <cstdint>
extern const bool ODOM_STATUS;
extern const bool LIVE_TUNING;

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
extern const std::int8_t LEFT_DRIVETRAIN_PORTS[];
extern const std::int8_t RIGHT_DRIVETRAIN_PORTS[];

extern const int INTAKE_MOTOR_PORT;
extern const int BACK_ROLLERS_PORT;
extern const int HOARD_MOTOR_PORT;
extern const int TOP_ROLLER_PORT;

extern const int TEST_PORT;

// Speeds
extern const double DRIVETRAIN_SPEED;
extern const double CONVEYOR_SPEED;
extern const double INTAKE_SPEED;



extern const double WHEEL_DIAMETER;
extern const double SIDEWAYS_ODOM_OFFSET;
extern const double FORWARD_ODOM_OFFSET;

#endif  // ROBOCONFIG_HPP