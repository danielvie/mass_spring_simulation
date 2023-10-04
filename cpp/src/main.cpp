#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct State {
    double x1, x2, v1, v2;
};

double M1, M2, k, c, Amp, omega, dt, t_end;
State initialState;

void readParameters() {
    std::ifstream paramFile("parameters.txt");
    if (!paramFile.is_open()) {
        std::cerr << "Failed to open parameters file." << std::endl;
        exit(-1);
    }

    std::string line, varName, equalsSign;
    while (getline(paramFile, line)) {
        std::istringstream lineStream(line);
        lineStream >> varName >> equalsSign;
        if (varName == "M1") lineStream >> M1;
        else if (varName == "M2") lineStream >> M2;
        else if (varName == "k") lineStream >> k;
        else if (varName == "c") lineStream >> c;
        else if (varName == "Amp") lineStream >> Amp;
        else if (varName == "omega") lineStream >> omega;
        else if (varName == "dt") lineStream >> dt;
        else if (varName == "t_end") lineStream >> t_end;
        else if (varName == "x1") lineStream >> initialState.x1;
        else if (varName == "x2") lineStream >> initialState.x2;
        else if (varName == "v1") lineStream >> initialState.v1;
        else if (varName == "v2") lineStream >> initialState.v2;
    }
    paramFile.close();
}

// External force F1
double F1(double t) {
    return Amp * std::sin(omega * t)*0;
}

// System dynamics
State systemDynamics(double t, const State& states) {
    double delta = states.x2 - states.x1;
    double a1 = (-k*states.x1 - c*states.v1 + k*delta + c*(states.v2 - states.v1) + F1(t)) / M1;
    double a2 = (-k*delta - c*(states.v2 - states.v1)) / M2;
    
    return {states.v1, states.v2, a1, a2};
}

// 4th Order Runge-Kutta Integration
State rungeKutta(double t, const State& states) {
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
    
    readParameters();

    std::ofstream logFile("states.log");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return -1;
    }

    // Logging the state values
    State currentState = initialState;
    for(double t = 0; t < t_end; t += dt) {
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