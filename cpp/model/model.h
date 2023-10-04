#include <fstream>
#include <iostream>
#include <sstream>
#include <iostream>
#include <memory>
#include "PIDController.h"
#include "types.h"

class Model
{
private:
    std::unique_ptr<PIDController> m_pid;


public:
    Model(/* args */);
    ~Model();

    void readParameters();
    State systemDynamics(double t, const State& states);
    State rungeKutta(double t, const State& states);
    double F1(double t);
    void step();
    
    double m_M1, m_M2, m_k, m_c, m_Amp, m_omega, m_dt, m_t_end, m_t;
    State m_initialState;
    State m_states;
};