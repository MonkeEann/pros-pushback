#include "main.h"

PID::PID(double kp, double ki, double kd)
    : kp(kp), ki(ki), kd(kd), error(0), prevError(0), integral(0), derivative(0) {}

void PID::reset() {
    error = 0;
    prevError = 0;
    integral = 0;
    derivative = 0;
}  
void PID::setConstants(double kp, double ki, double kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}
double PID::calculate(double target, double current) {
    prevError = error;

    error = target - current;
    double P = kp * error;

    integral += error;
    double I = ki * integral;

    derivative = error - prevError;
    double D = kd * derivative;

    return P + I + D;
}
double PID::getError() const {
    return error;
}
double PID::getprevError() const {
    return prevError;
}
