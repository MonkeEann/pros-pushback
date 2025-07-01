#ifndef PID_HPP
#define PID_HPP

class PID {
    private:
        double kp, ki, kd;
        double error, prevError, integral, derivative;

    public:
        PID(double kp, double ki, double kd);
        void reset();
        void setConstants(double kp, double ki, double kd);
        double calculate(double target, double current);

        double getError() const;
        double getprevError() const;

};

#endif
