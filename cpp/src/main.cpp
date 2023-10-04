#include "model.h"
#include <memory>

int main() {
    Model model;

    std::ofstream logFile("states.log");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return -1;
    }

    std::cout << "initial delta x1: " << model.m_states.x1 << std::endl;
    std::cout << "initial delta x2: " << model.m_states.x2 << std::endl;

    // Logging the state values
    while(model.m_t <= model.m_t_end) {
        logFile << model.m_t << ","
            << model.m_states.x1 << ","
            << model.m_states.x2 << ","
            << model.m_states.v1 << ","
            << model.m_states.v2 << std::endl;

        // make a step of simulation
        model.step();
    }

    logFile.close();

    std::cout << "final delta x1: " << model.m_states.x1 << std::endl;
    std::cout << "final delta x2: " << model.m_states.x2 << std::endl;

    return 0;
}