#include <fstream>
#include <iostream>
#include <sstream>
#include <iostream>

struct State {
    double x1, x2, v1, v2;
};

class Model
{
private:


public:
    Model(/* args */);
    ~Model();

    void readParameters();
    
    double M1, M2, k, c, Amp, omega, dt, t_end;
    State initialState;
    State states;
};