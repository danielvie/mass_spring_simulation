#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "types.h"

class PIDController {
private:
    double m_Kp, m_Ki, m_Kd; 
    double m_dt;
    double m_prevError; 
    double m_integral;  

public:

    // Constructor
    PIDController(double Kp, double Ki, double Kd, double dt);

    // Compute the PID control action
    double compute(double setpoint, const State& states);
};

#endif // PID_CONTROLLER_H
