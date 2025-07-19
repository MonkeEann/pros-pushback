#ifndef SUBGLOBALS_HPP
#define SUBGLOBALS_HPP

#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/ai_vision.hpp"


/* PORT CONFIG */
 /* Brain & Controller */
extern pros::Controller master;
extern pros::Imu imu;

/* Sensors */
extern pros::AIVision monke_vision;

/* Motors */
/* DRIVETRAIN MOTORS */
extern pros::MotorGroup leftDrivetrain;
extern pros::MotorGroup rightDrivetrain;

/* CONVEYOR/INTAKE MOTORS */
extern pros::Motor intakeMotor;
extern pros::Motor backRollersMotor;
extern pros::Motor hoardMotor;
extern pros::Motor topRollerMotor;

#endif // SUBGLOBALS_HPP