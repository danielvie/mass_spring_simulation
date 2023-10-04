#include <cmath>
#include <string>
#include <vector>
#include "model.h"

Model model;


// External force F1
double F1(double t) {
    return model.m_Amp * std::sin(model.m_omega * t)*0;
}

// System dynamics
State systemDynamics(double t, const State& states) {
    const double M1 = model.m_M1;
    const double M2 = model.m_M2;
    const double k = model.m_k;
    const double c = model.m_c;

    double delta = states.x2 - states.x1;
    double a1 = (-k*states.x1 - c*states.v1 + k*delta + c*(states.v2 - states.v1) + F1(t)) / M1;
    double a2 = (-k*delta - c*(states.v2 - states.v1)) / M2;
    
    return {states.v1, states.v2, a1, a2};
}

// 4th Order Runge-Kutta Integration
State rungeKutta(double t, const State& states) {
    
    const double dt = model.m_dt;

    State k1 = systemDynamics(t, states);
    State k2 = systemDynamics(t + 0.5*dt, {states.x1 + 0.5*dt*k1.x1, states.x2 + 0.5*dt*k1.x2, states.v1 + 0.5*dt*k1.v1, states.v2 + 0.5*dt*k1.v2});
    State k3 = systemDynamics(t + 0.5*dt, {states.x1 + 0.5*dt*k2.x1, states.x2 + 0.5*dt*k2.x2, states.v1 + 0.5*dt*k2.v1, states.v2 + 0.5*dt*k2.v2});
    State k4 = systemDynamics(t + dt, {states.x1 + dt*k3.x1, states.x2 + dt*k3.x2, states.v1 + dt*k3.v1, states.v2 + dt*k3.v2});
    
    return {
        states.x1 + dt/6.0 * (k1.x1 + 2.0*k2.x1 + 2.0*k3.x1 + k4.x1),
        states.x2 + dt/6.0 * (k1.x2 + 2.0*k2.x2 + 2.0*k3.x2 + k4.x2),
        states.v1 + dt/6.0 * (k1.v1 + 2.0*k2.v1 + 2.0*k3.v1 + k4.v1),
        states.v2 + dt/6.0 * (k1.v2 + 2.0*k2.v2 + 2.0*k3.v2 + k4.v2)
    };
}

int main() {
    // State initialState = {0, 0.5, 0, 0};
    
    // readParameters();

    std::ofstream logFile("states.log");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return -1;
    }

    // Logging the state values
    State currentState = model.m_initialState;
    for(double t = 0; t < model.m_t_end; t += model.m_dt) {
        logFile << t << ","
            << currentState.x1 << ","
            << currentState.x2 << ","
            << currentState.v1 << ","
            << currentState.v2 << std::endl;

        currentState = rungeKutta(t, currentState);
    }

    logFile.close();

    std::cout << "final delta x1: " << currentState.x1 << std::endl;
    std::cout << "final delta x2: " << currentState.x2 << std::endl;

    return 0;
}