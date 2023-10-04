#include "model.h"
#include <memory>

int main() {
    
    std::unique_ptr<Model> model = std::make_unique<Model>();

    std::ofstream logFile("states.log");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return -1;
    }

    // Logging the state values
    while(model->m_t <= model->m_t_end) {
        logFile << model->m_t << ","
            << model->m_states.x1 << ","
            << model->m_states.x2 << ","
            << model->m_states.v1 << ","
            << model->m_states.v2 << std::endl;

        // make a step of simulation
        model->step();
    }

    logFile.close();

    std::cout << "final delta x1: " << model->m_states.x1 << std::endl;
    std::cout << "final delta x2: " << model->m_states.x2 << std::endl;

    return 0;
}