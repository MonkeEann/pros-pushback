#ifndef AUTO_GLOBALS_HPP
#define AUTO_GLOBALS_HPP
#include "lemlib/pose.hpp"
#include "pros/distance.hpp"
#include "string"
#include "vector"
#include <string>
//! Sensor Ports
// Included in this file because they're only used in auton routines
extern pros::Distance fDistanceSensor;

constexpr double DISTANCE_OFFSET = 8.25; // Offset from the front distance sensor to the center of the robot in inches, allows for accurate odometry updates
class auton {
    private:
        std::string name;
        void (*routine)();
        lemlib::Pose startPose;
    public:
        auton(std::string Name, void (*routineFunc)(), lemlib::Pose startPose);
        std::string getName() const;
        void run();
        lemlib::Pose getStartPose() const;
        
};
class autonManager {
    private:
        std::vector<auton> autons;
        int selectedAutonIndex = -1;

    public:
    void selectAuton(std::string name);
    void selectAuton(int index);
    void runSelectedAuton();
    void addAuton(std::string name, void (*routineFunc)(), lemlib::Pose startPose);
    void listAutons();
    int getAutonNum() const;
    std::string getSelectedAutonName() const;
    std::string getAutonName(int index) const;
    lemlib::Pose getSelectedAutonStartPose() const;
    void setRobotStartPoseToSelectedAuton();
    
};
//* Helper Functions
void jerkMotion();
void updateOdomWithDistance();

//! Auton Routines
void configureAutons();
void LAutonCenterLong();
void RAutonCenterLong();
void LWinPoint();
void taxiAuton();
void skillsAuton();
#endif // AUTO_GLOBALS_HPP