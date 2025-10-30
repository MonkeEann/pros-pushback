#ifndef SUBGLOBALS_HPP
#define SUBGLOBALS_HPP

#include "lemlib/chassis/chassis.hpp"
#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"
#include "pros/ai_vision.hpp"
#include "pros/rotation.hpp"
#include "pros/adi.hpp"



/* Tasks */
/* Brain & Controller */
extern pros::Controller master;
extern pros::Imu imu;

/* Sensors */
extern pros::AIVision monke_vision;
extern pros::Rotation horizontalRotation; 
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
extern pros::Motor topRollerMotor;

extern pros::adi::Pneumatics foldPiston1;
extern pros::adi::Pneumatics foldPiston2;
extern pros::adi::Pneumatics matchLoadPiston;

// current Pose
extern lemlib::Pose currentPose;


#endif // SUBGLOBALS_HPP