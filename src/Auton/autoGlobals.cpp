#include "auton/autoGlobals.hpp"
#include "classDefine.hpp"
#include "lemlib/pose.hpp"
#include "subsystems/subGlobals.hpp"
#include <cstdio>
#include <iostream>

auton::auton(std::string Name, void (*routineFunc)(), lemlib::Pose startPose)
    :name(Name), routine(routineFunc), startPose(startPose) {}

std::string auton::getName() const { return name;};

void auton::run() {
    if(routine){ 
        routine(); 
    }
}
lemlib::Pose auton::getStartPose() const { return startPose;};
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
void autonManager::addAuton(std::string name, void (*routineFunc)(), lemlib::Pose startPose){
    autons.emplace_back(name, routineFunc, lemlib::Pose(startPose));
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
lemlib::Pose autonManager::getSelectedAutonStartPose() const{
    if (selectedAutonIndex != -1){
        return autons[selectedAutonIndex].getStartPose();
    } else {
        return lemlib::Pose(0,0,0);
    }
}
void autonManager::setRobotStartPoseToSelectedAuton(){
    if (selectedAutonIndex != -1){
        lemlib::Pose startPose = autons[selectedAutonIndex].getStartPose();
        monkeChassis.setPose(startPose.x, startPose.y, startPose.theta);

        char buffer[100];
        snprintf(buffer, sizeof(buffer), "Starting Pose: X: %.2f Y: %.2f Theta: %.2f \n",
                startPose.x, 
                startPose.y, 
                startPose.theta);
        std::cout << buffer;
    } else {
        std::cout << "No auton selected to set robot pose." << std::endl;
    }
}

void LAutonCenterLong(){
    printf("Running Left Winpoint Auton \n");
    //* MOVE TO 3 BLOCKS 
    monkeChassis.moveToPose(35, -24, 270, 5000, {.maxSpeed = 55, .minSpeed = 45}, true); // Move in front of 3 blocks
    //* Start intaking blocks
    monkeConveyor.storeBlocks();
    /* MOVE TO CENTER HIGH GOAL */
    monkeChassis.moveToPose(8.5, -7.5,315, 5000, {.horizontalDrift = 8, .minSpeed = 70}, true);
    monkeChassis.turnToHeading(310, 1000, {.maxSpeed = 60});
    
    ////monkeChassis.moveToPoint(9, -9, 3000, {.maxSpeed = 70}, true); // Move in front of center high goal
    pros::delay(250); // Delay So blocks don't score before Aligned
    
    //ff SCORE ON CENTER UPPER GOAL 
    monkeConveyor.scoreMid(); // Score the blocks
    pros::c::delay(2000); // Wait for scoring to finish
    monkeConveyor.stopConveyor();
    
    // MOVE IN FRONT OF MATCHLOADER 
    monkeChassis.moveToPoint(44,-45, 3000, {.forwards = false, .maxSpeed = 65}, false);
    monkeChassis.turnToHeading(90, 2000, {}, true);
    
    // MATCHLOAD 
    monkeConveyor.matchLoad();
    monkeConveyor.storeBlocks();
    monkeChassis.moveToPose(61,-45, 90, 2000, {.maxSpeed = 70, .minSpeed = 50}, true);
    monkeChassis.moveToPose(61,-45, 90, 850, {.maxSpeed = 70, .minSpeed = 50}, true);    
    
    // SCORE ON LONG GOAL 
    monkeChassis.moveToPose(40,-45, 90, 4000, {.forwards = false, .maxSpeed = 80, .minSpeed = 60});
    monkeConveyor.matchLoad(); // Flip Matchloader Back Up

    monkeChassis.turnToHeading(270, 2000, {.maxSpeed = 70}, false);
    monkeChassis.moveToPose(26.5,-45.5, 270, 4000, {.maxSpeed = 55, .minSpeed = 55}, true);
    monkeChassis.turnToHeading(270, 1000);
    monkeConveyor.scoreHigh();
    pros::delay(5000); 
    

}
void RAutonCenterLong(){
    printf("Running Left Winpoint Auton \n");
    /* MOVE TO 3 BLOCKS */
    monkeChassis.moveToPose(35, 24, 270, 5000, {.maxSpeed = 55, .minSpeed = 45}, true); // Move in front of 3 blocks
     // Start intaking blocks
    monkeConveyor.storeBlocks();
    /* MOVE TO CENTER HIGH GOAL */
    monkeChassis.moveToPose(8.75, 7.75,225, 5000, {.horizontalDrift = 8, .minSpeed = 70}, true);
    monkeChassis.turnToHeading(220, 1000, {.maxSpeed = 60});
    
    //monkeChassis.moveToPoint(9, -9, 3000, {.maxSpeed = 70}, true); // Move in front of center high goal
    pros::delay(250); // Delay So blocks don't score before Aligned
    
    //ff SCORE ON CENTER UPPER GOAL 
    monkeConveyor.scoreLow(); // Score the blocks
    pros::c::delay(2000); // Wait for scoring to finish
    monkeConveyor.stopConveyor();
    
    // MOVE IN FRONT OF MATCHLOADER 
    monkeChassis.moveToPoint(44,46, 3000, {.forwards = false, .maxSpeed = 65}, false);
    monkeChassis.turnToHeading(90, 2000, {}, true);

    // MATCHLOAD 
    monkeConveyor.matchLoad();
    monkeConveyor.storeBlocks();
    monkeChassis.moveToPose(61,46, 90, 2000, {.maxSpeed = 70, .minSpeed = 50}, true);
    monkeChassis.moveToPose(61,46, 90, 2000, {.maxSpeed = 70, .minSpeed = 50}, true);
    pros::delay(500);
    
    
    // SCORE ON LONG GOAL 
    monkeChassis.moveToPose(40,46, 90, 4000, {.forwards = false, .maxSpeed = 80, .minSpeed = 60});
    monkeConveyor.matchLoad(); // Flip Matchloader Back Up

    monkeChassis.turnToHeading(270, 2000, {.maxSpeed = 70}, false);
    monkeChassis.moveToPose(27,47.4, 270, 4000, {.maxSpeed = 55, .minSpeed = 55}, true);
    monkeChassis.turnToHeading(270, 1000);
    monkeConveyor.scoreHigh();
    pros::delay(5000);     
}
void LWinPoint(){
    printf("Running Left Red Winpoint Auton \n");
    /* SCORING ON CENTER HIGH GOAL */
    monkeConveyor.storeBlocks(); // START INTAKING BLOCKS
    monkeChassis.moveToPose(20, -24, 270, 5000, {.horizontalDrift = 8, .maxSpeed = 65, .minSpeed = 45}, true); // MOVE TO CORNER 3 BLOCKS
    monkeChassis.moveToPose(6, -8.5,315, 5000, {.horizontalDrift = 8, .minSpeed = 55, .earlyExitRange = 1}, true); // MOVE TO CENTER HIGH GOAL
    monkeChassis.turnToHeading(310, 1000, {.maxSpeed = 60}); // SLIGHT TURN FOR ALIGNMENT
    pros::delay(250); // Delay So blocks don't score before Aligned
    monkeConveyor.scoreMid(); // Score the blocks
    pros::c::delay(2000); // Wait for scoring to finish
    monkeConveyor.stopConveyor();

    /* MATCHLOADING */
    monkeChassis.moveToPoint(44,-46, 3000, {.forwards = false, .maxSpeed = 55}, false); // MOVE IN FRONT OF MATCHLOADER 
    monkeChassis.turnToHeading(90, 2000, {}, true); // TURN TOWARDS MATCHLOADER
    monkeConveyor.matchLoad(); // PUT MATCHLOADER DOWN
    monkeConveyor.storeBlocks(); // INTAKE IN MATCHLOADED BLOCKS
    monkeChassis.moveToPose(61,-46, 90, 2000, {.maxSpeed = 70, .minSpeed = 50}, true); // PUSH INTO MATCHLOADER
    monkeChassis.moveToPose(61,-46, 90, 500, {.maxSpeed = 70, .minSpeed = 50}, true); // PUSH INTO MATCHLOADER
    pros::delay(500); // WAIT FOR BLOCKS TO FALL IN

    // SCORE ON LEFT LONG GOAL 
    monkeChassis.moveToPose(45,-47, 90, 4000, {.forwards = false, .maxSpeed = 80, .minSpeed = 60}); // MOVE OUT OF MATCHLOADER
    monkeConveyor.matchLoad(); // Flip Matchloader Back Up
    monkeChassis.turnToHeading(270, 2000, {.maxSpeed = 70}, false); // TURN TOWARDS LONG GOAL
    monkeChassis.moveToPoint(36,-47.5, 2000, {.maxSpeed = 55, .minSpeed = 55}, true); // MOVE TO LONG GOAL
    monkeChassis.turnToHeading(270, 1000); // ALIGN TO LONG GOAL
    monkeConveyor.scoreHigh(); // SCORE ON LONG GOAL
    pros::delay(2000); // WAIT FOR SCORING TO FINISH

    /* SCORE ON RIGHT LONG GOAL */
    monkeChassis.moveToPoint(monkeChassis.getPose().x + 5,monkeChassis.getPose().y, 2000, {.forwards = false, .maxSpeed = 55, .minSpeed = 55}, true); // MOVE AWAY FROM LONG GOAL
    monkeConveyor.storeBlocks(); // INTAKE 3 BLOCKS RIGHT SIDE
    monkeChassis.moveToPose(22,30, 0, 2000, {.horizontalDrift = 8, .lead = .2, .minSpeed = 65}, true); // MOVE TO RIGHT SIDE 3 BLOCKS
    monkeChassis.turnToHeading(90, 2000, {.maxSpeed = 65});
    monkeChassis.moveToPose(40,38, 0, 4000, {.maxSpeed = 85, .minSpeed = 65, .earlyExitRange = 2}, true); // MOVE TO RIGHT LONG GOAL
    monkeChassis.moveToPose(32,56.25, 270, 3000, {.maxSpeed = 55, .earlyExitRange = 1 }, true); // MOVE TO RIGHT LONG GOAL
    monkeChassis.moveToPose(27.25,56.25, 270, 3000, {.maxSpeed = 55}, true); // MOVE TO RIGHT LONG GOAL
    pros::delay(500); // WAIT FOR ALIGNMENT
    monkeConveyor.scoreHigh(); // SCORE ON LONG GOAL
    pros::delay(5000);
}
void taxiAuton(){
    printf("Running Taxi Auton \n");
    monkeChassis.moveToPoint(monkeChassis.getPose().x + 10, monkeChassis.getPose().y, 5000);
}

void configureAutons(){
    autonMgr.addAuton("L Auton", LAutonCenterLong, lemlib::Pose(62.5, -18, 180));
    autonMgr.addAuton("R Auton", RAutonCenterLong, lemlib::Pose(62.5, 18, 0));
    autonMgr.addAuton("L WP", LWinPoint, lemlib::Pose(62.5, -18, 180));
    autonMgr.addAuton("Taxi", taxiAuton, lemlib::Pose(0, 0, 90));
    
    autonMgr.selectAuton(0); // Default to first auton
    autonMgr.setRobotStartPoseToSelectedAuton();
}