#ifndef SUBGLOBALS_HPP
#define SUBGLOBALS_HPP

#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"
#include "pros/ai_vision.hpp"
#include "pros/rotation.hpp"
#include "pros/adi.hpp"
#include "lemlib/api.hpp"



/* Tasks */
/* Brain & Controller */
extern pros::Controller master;
extern pros::Imu imu;

/* Sensors */
extern pros::AIVision monke_vision;
extern pros::Rotation horizontalRotaion; 
extern pros::Rotation verticalRotaion; 


/* DRIVETRAIN  */
extern pros::MotorGroup leftDrivetrain;
extern pros::MotorGroup rightDrivetrain;
extern lemlib::Drivetrain monkeDrivetrain;

extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve turnCurve;
extern lemlib::Chassis monkeChassis;

/* CONVEYOR/INTAKE MOTORS */
extern pros::Motor intakeMotor;
extern pros::Motor backRollersMotor;
extern pros::Motor hoardMotor;
extern pros::Motor topRollerMotor;

extern pros::ADIDigitalOut hoodPiston;
extern pros::ADIDigitalOut matchLoadPiston;

// current Pose
extern lemlib::Pose currentPose;


#endif // SUBGLOBALS_HPP