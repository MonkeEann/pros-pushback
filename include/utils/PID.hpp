#ifndef PID_HPP
#define PID_HPP

class PID {
    private:
        double kP, kI, kD;
        double error, prevError, integral, derivative;

    public:
        PID(double kp, double ki, double kd);
        void reset();
        void setConstants(double kp, double ki, double kd);
        double calculate(double target, double current);

        double getkP() const;
        double getkI() const;
        double getkD() const;
        double getError() const;
        double getprevError() const;

};

#endif
