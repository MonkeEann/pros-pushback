#include "subsystems/subGlobals.hpp"
#include "roboConfig.hpp"
#include "classDefine.hpp"
/*
 * Global instances of various subsystems
 * This file is used to declare global variables that will be used across multiple files. 
 */
/* Tasks */
pros::Task* odomTask = nullptr;

 /* Brain & Controller */
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Imu imu(20);

/* Sensors */
pros::AIVision monke_vision(1);

pros::Rotation horizontalRotation(11);
pros::Rotation verticalRotaion(12);

pros::adi::Pneumatics foldPiston1(FOLD_PISTON_1_PORT, isConveyorUp);
pros::adi::Pneumatics foldPiston2(FOLD_PISTON_2_PORT, isConveyorUp);
pros::adi::Pneumatics matchLoadPiston(MATCH_LOAD_PORT, false);

/* Conveyor Motors */
pros::Motor intakeMotor(INTAKE_MOTOR_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor backRollersMotor(BACK_ROLLERS_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor topRollerMotor(TOP_ROLLER_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);
pros::Motor testMotor(TEST_PORT, pros::MotorGearset::green, pros::MotorEncoderUnits::degrees);

Conveyor monkeConveyor(backRollersMotor, intakeMotor, topRollerMotor, CONVEYOR_SPEED);

/* Drivetrain */
pros::MotorGroup leftDrivetrain({LEFT_DRIVETRAIN_PORTS[0],LEFT_DRIVETRAIN_PORTS[1], LEFT_DRIVETRAIN_PORTS[2]}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);
pros::MotorGroup rightDrivetrain({RIGHT_DRIVETRAIN_PORTS[0], RIGHT_DRIVETRAIN_PORTS[1], RIGHT_DRIVETRAIN_PORTS[2]}, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);
lemlib::Drivetrain monkeDrivetrain(&leftDrivetrain,
                                    &rightDrivetrain,
                                    13, // track width
                                    lemlib::Omniwheel::NEW_275, 
                                    450, // drivetrain rpm
                                    2);
                                    
lemlib::TrackingWheel horizontalTrackingWheel(&horizontalRotation, lemlib::Omniwheel::NEW_2, -4.25);
lemlib::TrackingWheel verticalTrackingWheel(&verticalRotaion, lemlib::Omniwheel::NEW_2, 0);

lemlib::OdomSensors sensors(&verticalTrackingWheel,
                            nullptr,
                            &horizontalTrackingWheel,
                            nullptr,
                            &imu);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(50, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              1000, // small error range timeout, in milliseconds
                                              5, // large error range, in inches
                                              2000, // large error range timeout, in milliseconds
                                              3 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(ANGULAR_PID_KP, // proportional gain (kP)
                                              ANGULAR_PID_KI, // integral gain (kI)
                                              ANGULAR_PID_KD, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(JOYSTICK_DEADBAND, // joystick deadband out of 127
                                     DRIVETRAIN_DEADBAND, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve turnCurve(JOYSTICK_DEADBAND, // joystick deadband out of 127
                                 DRIVETRAIN_DEADBAND, // minimum output where drivetrain will move out of 127
                                 1.019 // expo curve gain
);
lemlib::Chassis monkeChassis(monkeDrivetrain,
                            lateral_controller,
                            angular_controller,
                            sensors,
                            &throttleCurve,
                            &turnCurve
);