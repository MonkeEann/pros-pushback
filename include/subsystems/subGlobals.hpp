#ifndef SUBGLOBALS_HPP
#define SUBGLOBALS_HPP

#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/ai_vision.hpp"
#include "pros/rotation.hpp"

/* Tasks */
extern pros::Task* odomTask;
void odomTaskFn(void* param);

/* Brain & Controller */
extern pros::Controller master;
extern pros::Imu imu;

/* Sensors */
extern pros::AIVision monke_vision;
extern pros::Rotation sidewaysRotaion; 
extern pros::Rotation forwardRotaion; 

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