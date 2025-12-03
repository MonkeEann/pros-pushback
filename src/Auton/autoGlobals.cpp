#include "auton/autoGlobals.hpp"
#include "classDefine.hpp"
#include "lemlib/pose.hpp"
#include "pros/rtos.hpp"
#include "roboConfig.hpp"
#include "subsystems/subGlobals.hpp"
#include <cstdio>
#include <iostream>
//! Distance Sensors Definitions
pros::Distance fDistanceSensor(FRONT_DISTANCE_SENSOR_PORT);

//* Class Definitions
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

//* Function Definitions
void updateOdomWithDistance(){
    double distance = fDistanceSensor.get()/25.4;

    double theta = monkeChassis.getPose().theta;
    double deltaTheta;
    double x = monkeChassis.getPose().x;
    double y = monkeChassis.getPose().y;

    while(theta < 0) theta += 360;
    while(theta >= 360) theta -= 360;

    const double ANGLE_TOLERANCE = 2.0; // degrees
    /* 
    ! To calculate the position we take the adjustedDistance and subtract it from the position of the wall on the field
    ! Since we have (0, 0) at the center of the field and the entire field is 144in x 144in, the walls are at +/- 72in, they are 2in thick making the inside edge at +/- 70in
    */
    // Facing Positive Y Direction
    if (fabs(theta - 0) <= ANGLE_TOLERANCE || fabs(theta - 360) <= ANGLE_TOLERANCE){
        double deltaTheta = theta;
        if (deltaTheta > 180) deltaTheta = 360 - deltaTheta;
        printf("Facing 0... Calculating Y Position \n");

        double adjustedDistance = DISTANCE_OFFSET + (distance * cos((deltaTheta * (M_PI / 180.0))));
        y = 70 - adjustedDistance;
        printf("Updated Y Position: %.2f \n", y);
    } 
    else if(fabs(theta - 180) <= ANGLE_TOLERANCE){
        // If it is facing 180 degrees the y axis is negative so the wall is at y = -72
        // Instead of subtracting we add the adjusted distance
        double deltaTheta = fabs(180 - theta);
        printf("Facing 180... Calculating Y Position \n");

        double straightlineDistance = distance * cos((deltaTheta * (M_PI / 180.0)));
        double adjustedDistance = DISTANCE_OFFSET + straightlineDistance;
        y = -70 + adjustedDistance;
        printf("Updated Y Position: %.2f \n", y);
    } 
    else if (fabs(theta - 90) <= ANGLE_TOLERANCE){
        double deltaTheta = fabs(90 - theta);
        printf("Facing 90... Calculating X Position \n");

        double adjustedDistance = DISTANCE_OFFSET + (distance * cos((deltaTheta * (M_PI / 180.0))));
        x = 70 - adjustedDistance;
        printf("Updated X Position: %.2f \n", x);
        } 
    else if(fabs(theta - 270) <= ANGLE_TOLERANCE){
        double deltaTheta = fabs(270 - theta);
        printf("Facing 270... Calculating X Position \n");

        double adjustedDistance = DISTANCE_OFFSET + (distance * cos((deltaTheta * (M_PI / 180.0))));
        x = -70 + adjustedDistance;
        printf("Updated X Position: %.2f \n", x);
    }
    monkeChassis.setPose(x, y, monkeChassis.getPose().theta);
}

void jerkMotion(){
    monkeChassis.moveToPose(monkeChassis.getPose().x + 5, monkeChassis.getPose().y, monkeChassis.getPose().theta, 1000, {.forwards = false, .minSpeed = 100});
    monkeChassis.moveToPose(monkeChassis.getPose().x - 5, monkeChassis.getPose().y, monkeChassis.getPose().theta, 1000, {.minSpeed = 80}, true);
}
void LAutonCenterLong(){
    printf("Running Left Winpoint Auton \n");
    //* MOVE TO 3 BLOCKS 
    monkeChassis.moveToPose(35, -24, 270, 5000, {.maxSpeed = 55, .minSpeed = 45}, true); // Move in front of 3 blocks
    //* Start intaking blocks
    monkeConveyor.storeBlocks();
    /* MOVE TO CENTER HIGH GOAL */
    monkeChassis.moveToPose(8, -7.5,315, 5000, {.horizontalDrift = 8, .minSpeed = 55                        }, true);
    monkeChassis.turnToHeading(310, 1000, {.maxSpeed = 60});
    
    ////monkeChassis.moveToPoint(9, -9, 3000, {.maxSpeed = 70}, true); // Move in front of center high goal
    pros::delay(250); // Delay So blocks don't score before Aligned
    
    //* SCORE ON CENTER UPPER GOAL 
    monkeConveyor.scoreMid(); // Score the blocks
    pros::c::delay(2000); // Wait for scoring to finish
    monkeConveyor.stopConveyor();
    
    // MOVE IN FRONT OF MATCHLOADER 
    monkeChassis.moveToPoint(44,-45, 3000, {.forwards = false, .maxSpeed =70}, false);
    monkeChassis.turnToHeading(90, 2000, {}, true);
    
    // MATCHLOAD 
    monkeConveyor.matchLoad();
    monkeConveyor.storeBlocks();
    monkeChassis.moveToPose(61,-45, 90, 1350, {.maxSpeed = 85}, true);
    
    // SCORE ON LONG GOAL 
    monkeChassis.moveToPose(40,-45, 90, 4000, {.forwards = false, .maxSpeed = 80, .minSpeed = 60});
    monkeConveyor.matchLoad(); // Flip Matchloader Back Up

    monkeChassis.turnToHeading(270, 2000, {.maxSpeed = 70}, false);
    monkeChassis.moveToPose(26,-45.5, 272, 4000, {.maxSpeed = 55, .minSpeed = 55}, true);
    monkeChassis.moveToPose(25,-45.5, 272, 4000, {.maxSpeed = 60, .minSpeed = 60}, true);
    monkeChassis.turnToHeading(275, 1000);
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
    monkeChassis.moveToPose(8, 7.5,225, 5000, {.horizontalDrift = 8, .minSpeed = 70}, true);
    monkeChassis.turnToHeading(215, 1000, {.maxSpeed = 60});
    
    //monkeChassis.moveToPoint(9, -9, 3000, {.maxSpeed = 70}, true); // Move in front of center high goal
    pros::delay(250); // Delay So blocks don't score before Aligned
    
    //ff SCORE ON CENTER UPPER GOAL 
    monkeConveyor.scoreLow(); // Score the blocks
    pros::c::delay(2000); // Wait for scoring to finish
    monkeConveyor.stopConveyor();
    
    // MOVE IN FRONT OF MATCHLOADER 
    monkeChassis.moveToPoint(44,46, 3000, {.forwards = false, .maxSpeed = 75}, false);
    monkeChassis.turnToHeading(90, 2000, {}, true);

    // MATCHLOAD 
    monkeConveyor.matchLoad();
    monkeConveyor.storeBlocks();
    monkeChassis.moveToPose(61,47, 90, 2000, {.maxSpeed = 70, .minSpeed = 50}, true);
    monkeChassis.moveToPose(61,47, 90, 2000, {.maxSpeed = 70, .minSpeed = 50}, true);
    
    
    // SCORE ON LONG GOAL 
    monkeChassis.moveToPose(40,46, 90, 4000, {.forwards = false, .maxSpeed = 80, .minSpeed = 60});
    monkeConveyor.matchLoad(); // Flip Matchloader Back Up

    monkeChassis.turnToHeading(270, 2000, {.maxSpeed = 70}, false);
    monkeChassis.moveToPose(25.,47, 270, 4000, {.maxSpeed = 45, .minSpeed = 40}, true);
    monkeChassis.turnToHeading(275, 1000);
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
void skillsAuton(){
    printf("Running Skills Auton \n");
    monkeConveyor.storeBlocks(); // Start Intaking Blocks
    monkeChassis.moveToPose(-45, -50, 270, 3000, {.maxSpeed = 70}, false); // Move To Red Right Matchloader
    monkeChassis.turnToHeading(270, 2000, {.maxSpeed = 60}, false);
    monkeConveyor.matchLoad(); // Lower Matchloader
    monkeConveyor.storeBlocks(); // Start Intaking Blocks
    monkeChassis.moveToPose(-62.5, -50, 270, 3000, {.maxSpeed = 90, .minSpeed = 85}); // Ensure It goes into matchloader
    monkeChassis.moveToPose(-62.5, -50, 270, 2000, {.maxSpeed = 90, .minSpeed = 85}); // Ensure It goes into matchloader
    pros::delay(2000); // Wait for blocks to loader
    monkeConveyor.stopConveyor();
    monkeConveyor.matchLoad(); // Raise Matchloader
    monkeChassis.moveToPose(-40, -67, 270, 3000, {.forwards = false}); // Back away from matchloader
    monkeChassis.moveToPose(35, -67, 270, 3000, {.forwards = false, .maxSpeed = 75}, false); // Head to blue right matchloader
    updateOdomWithDistance(); // Update Odom with distance sensor reading
    /*monkeChassis.moveToPose(53, -54, 270, 3000, {.forwards = false, .maxSpeed = 75}, false); // Line up with Long goal
    //jerkMotion(); 
    monkeChassis.moveToPose(35.75, -54.75, 270, 3000, {.maxSpeed = 60}, false); // Align with long goal   
    monkeConveyor.scoreHigh(); // Score on long goal
    pros::delay(4000);
    monkeChassis.moveToPose(45, -54, 270, 3000, {.forwards = false, .maxSpeed = 60}, true); // Back away from long goal
    monkeChassis.turnToHeading(90, 3000, {.maxSpeed = 60}, true); // Turn Around
    monkeConveyor.matchLoad();
    monkeConveyor.storeBlocks(); // Start Intaking Blocks
    monkeChassis.moveToPose(64, -53.5, 93, 3000, {.maxSpeed = 90, .minSpeed = 90}); // Move into Blue right matchloader
    monkeChassis.moveToPose(64, -54, 93, 2000, {.minSpeed = 85}); // Move into Blue right matchloader
    pros::delay(2000);
    monkeConveyor.stopConveyor();
    monkeConveyor.matchLoad(); // Raise Matchloader
    monkeChassis.moveToPose(45, -53, 90, 1000, {.forwards = false, .minSpeed = 85}, false); // Move into Blue right matchloader  
    monkeChassis.turnToHeading(270, 3000, {.maxSpeed = 60}, true); // Turn Around
    monkeChassis.moveToPose(34.5, -53.25, 270, 3000, {.maxSpeed = 60}, false); // Align with long goal   
    monkeConveyor.scoreHigh(); // Score on long goal
    pros::delay(4000);
    monkeChassis.moveToPose(53, -53, 90, 1000, {.forwards = false, .minSpeed = 85}, true); // Move into Blue right matchloader  
    monkeChassis.turnToHeading(0, 3000, {.maxSpeed = 60}, true); // Turn Around 

    monkeChassis.moveToPose(53, -26, 0, 1000, {.minSpeed = 85}, false); // Move into Blue right matchloader  
    monkeChassis.moveToPose(-65, -30, 270, 5000, {.minSpeed = 85}, false); // Move into Blue right matchloader  
    monkeChassis.moveToPose(-68, -30, 270, 5000, {.minSpeed = 20}, true); // Move into Blue right matchloader  
    monkeChassis.turnToHeading(0, 3000, {.maxSpeed = 60}, true); // Turn Around
    monkeConveyor.scoreLow(); //Push blocks away from bot
    monkeChassis.moveToPose(-66.5, 0, 0, 3000, {.minSpeed = 90});
    pros::delay(1500);
    monkeConveyor.stopConveyor();
    */
    

}

void configureAutons(){
    autonMgr.addAuton("L Auton", LAutonCenterLong, lemlib::Pose(62.5, -18, 180));
    autonMgr.addAuton("R Auton", RAutonCenterLong, lemlib::Pose(62.5, 18, 0));
    autonMgr.addAuton("L WP", LWinPoint, lemlib::Pose(62.5, -18, 180));
    autonMgr.addAuton("Taxi", taxiAuton, lemlib::Pose(0, 0, 90));
    autonMgr.addAuton("Skills", skillsAuton, lemlib::Pose(-62.5, -18, 180));
    
    autonMgr.selectAuton(0); // Default to first auton
    autonMgr.setRobotStartPoseToSelectedAuton();
}