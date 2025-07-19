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
pros::MotorGroup leftDrivetrain({1, 2, 3}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);
pros::MotorGroup rightDrivetrain({-8, -9, -10}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);

/* Conveyor Motors */
pros::Motor intakeMotor(4, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor bottomBackMotor(5, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor hoardMotor(6, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor backConveyorMotors(7, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);


