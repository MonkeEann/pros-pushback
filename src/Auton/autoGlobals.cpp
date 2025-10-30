#include "auton/autoGlobals.hpp"
#include "classDefine.hpp"
#include "subsystems/subGlobals.hpp"
#include <cstdio>
#include <iostream>

auton::auton(std::string Name, void (*routineFunc)())
    :name(Name), routine(routineFunc) {}

std::string auton::getName() const { return name;};

void auton::run() {
    if(routine){ 
        routine(); 
    }
}
void autonManager::selectAuton(std::string name){
    for (int i = 0; i < (int)autons.size(); i++){
        if (autons[i].getName() == name){
            selectedAutonIndex = i;
            return;
        } else {
            std::cout << "Auton with name " << name << " not found." << std::endl;
        }
    }
}
void autonManager::selectAuton(int index){
    if (index >= 0 && index < (int)autons.size()) {
        selectedAutonIndex = index;
    } else {
        std::cout << "Invalid auton index selected" << std::endl;
    }
}
void autonManager::runSelectedAuton(){
    if (selectedAutonIndex != -1){
        autons[selectedAutonIndex].run();
    } else {
        std::cout << "No auton selected to run." << std::endl;
    }
}
void autonManager::addAuton(std::string name, void (*routineFunc)()){
    autons.emplace_back(name, routineFunc);
}
void autonManager::listAutons(){
    for(int i; i < (int)autons.size(); i++){
        std::cout << "Available Autons: " << std::endl;
        std::cout << i << ":" << autons[i].getName() << std::endl;
    }
}
int autonManager::getAutonNum() const{ return autons.size(); }
std::string autonManager::getSelectedAutonName() const{ return autons[selectedAutonIndex].getName(); }
std::string autonManager::getAutonName(int index) const{
    if (index >= 0 && index < (int)autons.size()){
        return autons[index].getName();
    } else {
        return "Invalid Index";
    }
}

void leftAutonWP(){
    printf("Running Left Winpoint Auton \n");
    monkeChassis.moveToPose(25, -31, 315, 4000, {.maxSpeed = 127*0.6}, false);
    monkeConveyor.storeBlocks();
    // Move to center high goal
    monkeChassis.moveToPose(10, -14, 315, 4000, {.maxSpeed = 64}, false);
    monkeConveyor.scoreMid();
    pros::c::delay(1000);
    monkeConveyor.stopConveyor();
    // Move to matchloader
    monkeChassis.moveToPose(44,-48, 315, 4000, {.forwards = false, .maxSpeed = 127*0.6});
    monkeChassis.turnToHeading(90, 4000, {}, false);
    //Move Into Loader
    monkeConveyor.matchLoad();
    monkeChassis.moveToPose(55,-49.5, 90, 4000, {.maxSpeed = 127*0.6});
    monkeConveyor.storeBlocks();
    pros::delay(1000);
    monkeConveyor.stopConveyor();
    // Score on long goal
    monkeChassis.moveToPose(40,-49.5, 270, 4000, {.forwards = false, .maxSpeed = 127*0.6});
    monkeConveyor.matchLoad();
    monkeChassis.turnToHeading(270, 2000);
    monkeChassis.moveToPose(27.5,-49.5, 270, 4000, {.maxSpeed = 127*0.6}, false);
    monkeConveyor.scoreHigh();
    pros::delay(5000);    
}
void rightAutonWP(){
    printf("Running Right Winpoint Auton \n");
}
void taxiAuton(){
    printf("Running Taxi Auton \n");
}
void longOnlyLeftAuton(){
    printf("Running Left Long Goal ONLY Auton \n");
}
void longOnlyRightAuton(){
    printf("Running Right Long Goal ONLY Auton \n");
}

void configureAutons(){
    autonMgr.addAuton("Left WP", leftAutonWP);
    autonMgr.addAuton("Right WP", rightAutonWP);
    autonMgr.addAuton("Taxi", taxiAuton);
    
    autonMgr.selectAuton(0); // Default to first auton
}