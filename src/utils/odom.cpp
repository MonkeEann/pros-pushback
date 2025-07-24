#include "Odom.hpp"
#include "subsystems/subGlobals.hpp"
#include <cmath>
#include "roboConfig.hpp"
#include "utils/utilGlobals.hpp"

Odom::Odom(const double& wheelD, const double& sS, const double& sF)
    : gX(0), gY(0), heading(0), prevHeading(0), prevForward(0), prevSideways(0), wheelDiameter(wheelD), sidewaysWheelOffset(sS), forwardWheelOffset(sF) {};

double Odom::getIMURadians(){
    double headingInRadians = imu.get_heading() * (M_PI / 180);
    return headingInRadians;
}
double Odom::degreesToDistance(double degrees){
    return (degrees/360) * (wheelDiameter * M_PI);
}

double Odom::getGlobalX() const { return gX; }
double Odom::getGlobalY() const { return gY; }
double Odom::getHeading() const { return heading; }

void Odom::setPosition(double x, double y){
    gX = x;
    gY = y;
    prevHeading = getIMURadians();
}
void Odom::updateOdom(){

    /* GET CURRENT READINGS */
    double currentHeading = getIMURadians();
    double currentSideways = degreesToDistance(sidewaysRotaion.get_position());
    double currentForward = degreesToDistance(forwardRotaion.get_position());

    /* CALCULATE DIFFERENCES FROM LAST CYCLE */
    double deltaHeading = currentHeading - prevHeading;
    double deltaForward = currentForward - prevForward;
    double deltaSideways = currentSideways - prevSideways;

    /* Calculate Cycle Offsets */
    double localOffsetX, localOffsetY;
    if (deltaHeading == 0)
    {
        localOffsetX = 0;
        localOffsetY = deltaForward;
    } else {
        localOffsetX = 2 * sin(deltaHeading/2) * (deltaSideways/deltaHeading) + sidewaysWheelOffset;
        localOffsetY = 2 * sin(deltaHeading/2) * (deltaForward/deltaHeading) + forwardWheelOffset; 
    }

    double avgInertial = prevHeading + deltaHeading / 2.0;

    /* Convert to global offsets */
    double globalOffsetX = localOffsetX * cos(-avgInertial) - localOffsetY * sin(-avgInertial);
    double globalOffsetY = localOffsetX * sin(-avgInertial) - localOffsetY * cos(-avgInertial);

    /* Update Position*/
    gX += globalOffsetX;
    gY += globalOffsetY;

    /* Update Previous Readings */
    prevHeading = currentHeading;
    prevForward = currentForward;
    prevSideways = currentSideways;
}

void odomInit(){
    if (ODOM_STATUS){
        odomTask = new pros::Task(odomTaskFn, nullptr, "Odom");
        printToTerminal(9, "ODOM STATUS: ON");
    } else {
        printf("Odom Off \n");
        printToTerminal(9, "ODOM STATUS: OFF");
    }
};