#include <cmath>
#include <string>
#include <vector>
#include "model.h"

Model model;

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

        currentState = model.rungeKutta(t, currentState);
    }

    logFile.close();

    std::cout << "final delta x1: " << currentState.x1 << std::endl;
    std::cout << "final delta x2: " << currentState.x2 << std::endl;

    return 0;
}