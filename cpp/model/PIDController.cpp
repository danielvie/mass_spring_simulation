#include "PIDController.h"


// Constructor definition
PIDController::PIDController(double Kp, double Ki, double Kd, double dt)
    : m_Kp(Kp), m_Ki(Ki), m_Kd(Kd), m_dt(dt), m_prevError(0), m_integral(0), m_on(false) {}

double PIDController::compute(double setpoint, const State& states) {
    double error = setpoint - states.x1;
    m_integral +=  error * m_dt;
    double derivative = -states.v1;

    double u = m_Kp * error + m_Ki * m_integral + m_Kd * derivative;

    m_prevError = error;
    
    if (m_on == false) {
        u = u * 0.0;
    }

    return u;
}

void PIDController::enable(bool value) {
    m_on = value;
}