#include "subsystems/subGlobals.hpp"

/*
 * Global instances of various subsystems
 * This file is used to declare global variables that will be used across multiple files. 
 */

 /* Brain & Controller */
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Imu imu(20);

/* Sensors */
pros::AIVision monke_vision(1);

/* Motors */
/* Drivetrain Motors */
pros::MotorGroup leftDrivetrain({LEFT_DRIVETRAIN_PORTS[0],LEFT_DRIVETRAIN_PORTS[1], LEFT_DRIVETRAIN_PORTS[2]}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);
pros::MotorGroup rightDrivetrain({RIGHT_DRIVETRAIN_PORTS[0], RIGHT_DRIVETRAIN_PORTS[1], RIGHT_DRIVETRAIN_PORTS[2]}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);

/* Conveyor Motors */
pros::Motor intakeMotor(INTAKE_MOTOR_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor backRollersMotor(BACK_ROLLERS_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor hoardMotor(HOARD_MOTOR_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor topRollerMotor(TOP_ROLLER_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);


