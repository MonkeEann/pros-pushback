#ifndef AUTO_GLOBALS_HPP
#define AUTO_GLOBALS_HPP
#include "lemlib/pose.hpp"
#include "string"
#include "vector"
#include <string>

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

void configureAutons();
void LAutonCenterLong();
void RAutonCenterLong();
void LWinPoint();
void taxiAuton();
void longOnlyLeftAuton();
void longOnlyRightAuton();
#endif // AUTO_GLOBALS_HPP