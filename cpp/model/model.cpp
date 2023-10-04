#include "model.h"

Model::Model(/* args */)
{
    std::cout << "model created!\n";
    readParameters();
}

Model::~Model()
{
    std::cout << "model destroyed!\n";
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