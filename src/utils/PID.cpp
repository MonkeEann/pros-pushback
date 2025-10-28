#include "utils/PID.hpp"

PID::PID(double kp, double ki, double kd) {
    setConstants(kp, ki, kd);
}

void PID::reset(){
    integral = 0;
    prevError = 0;
}
void PID::setConstants(double kp, double ki, double kd){
    kP = kp;
    kI = ki;
    kD = kd;
}
double PID::calculate(double target, double current){
    error = target - current;
    double P = kP * error;

    integral += error;
    double I = kI * integral;

    derivative = error - prevError;
    double D = kD * derivative; 
    prevError = error;

    return P + I + D;
}

double PID::getkP() const {return kP;}
double PID::getkI() const {return kI;}
double PID::getkD() const {return kD;}
double PID::getError()const {return error;}
double PID::getprevError() const {return prevError;}