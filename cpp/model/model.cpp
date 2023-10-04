#include "model.h"

Model::Model(/* args */)
{
    std::cout << "model created!\n";
    readParameters();
    
    m_states = m_initialState;
    m_t = 0.0;
}

Model::~Model()
{
    std::cout << "model destroyed!\n";
}

void Model::step() {
    m_states = rungeKutta(m_t, m_states);
    m_t += m_dt;
}

void Model::readParameters() {
    std::ifstream paramFile("parameters.txt");
    if (!paramFile.is_open()) {
        std::cerr << "Failed to open parameters file." << std::endl;
        exit(-1);
    }

    std::string line, varName, equalsSign;
    while (getline(paramFile, line)) {
        std::istringstream lineStream(line);
        lineStream >> varName >> equalsSign;
        if (varName == "M1") lineStream >> m_M1;
        else if (varName == "M2") lineStream >> m_M2;
        else if (varName == "k") lineStream >> m_k;
        else if (varName == "c") lineStream >> m_c;
        else if (varName == "Amp") lineStream >> m_Amp;
        else if (varName == "omega") lineStream >> m_omega;
        else if (varName == "dt") lineStream >> m_dt;
        else if (varName == "t_end") lineStream >> m_t_end;
        else if (varName == "x1") lineStream >> m_initialState.x1;
        else if (varName == "x2") lineStream >> m_initialState.x2;
        else if (varName == "v1") lineStream >> m_initialState.v1;
        else if (varName == "v2") lineStream >> m_initialState.v2;
    }
    paramFile.close();
}

// External force F1
double Model::F1(double t) {
    return m_Amp * std::sin(m_omega * t)*0;
}

// System dynamics
State Model::systemDynamics(double t, const State& states) {
    double delta = states.x2 - states.x1;
    double a1 = (-m_k*states.x1 - m_c*states.v1 + m_k*delta + m_c*(states.v2 - states.v1) + F1(t)) / m_M1;
    double a2 = (-m_k*delta - m_c*(states.v2 - states.v1)) / m_M2;
    
    return {states.v1, states.v2, a1, a2};
}

// 4th Order Runge-Kutta Integration
State Model::rungeKutta(double t, const State& states) {
    
    const double dt = m_dt;

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
