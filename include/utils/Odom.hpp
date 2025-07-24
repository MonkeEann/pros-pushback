#ifndef ODOM_HPP
#define ODOM_HPP

#include "pros/rotation.hpp"

void odomInit();
class Odom {
    private:

    double gX;
    double gY;
    double heading;
    double prevHeading;
    double prevForward;
    double prevSideways;
    const double wheelDiameter;
    const double sidewaysWheelOffset;
    const double forwardWheelOffset;

    public:
    Odom(const double& wheelD, const double& sS, const double& sF);

    double getIMURadians();
    double degreesToDistance(double degrees);
    double getGlobalX() const;
    double getGlobalY() const;
    double getHeading() const;
    void setPosition(double x, double y);
    void updateOdom();

};



#endif //ODOM_HPP