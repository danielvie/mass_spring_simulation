#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "types.h"

class PIDController {
private:
    double m_Kp, m_Ki, m_Kd;     // Proportional, Integral, and Derivative coefficients
    double m_prevError;          // Error from the previous step for derivative computation
    double m_integral;           // Accumulated integral of error

public:
    // Constructor
    PIDController(double Kp, double Ki, double Kd);

    // Compute the PID control action
    double compute(double setpoint, const State& states);
};

#endif // PID_CONTROLLER_H
