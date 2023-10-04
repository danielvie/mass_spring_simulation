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
        if (varName == "M1") lineStream >> this->M1;
        else if (varName == "M2") lineStream >> this->M2;
        else if (varName == "k") lineStream >> this->k;
        else if (varName == "c") lineStream >> this->c;
        else if (varName == "Amp") lineStream >> this->Amp;
        else if (varName == "omega") lineStream >> this->omega;
        else if (varName == "dt") lineStream >> this->dt;
        else if (varName == "t_end") lineStream >> this->t_end;
        else if (varName == "x1") lineStream >> this->initialState.x1;
        else if (varName == "x2") lineStream >> this->initialState.x2;
        else if (varName == "v1") lineStream >> this->initialState.v1;
        else if (varName == "v2") lineStream >> this->initialState.v2;
    }
    paramFile.close();
}