#pragma once
#include <string>

class Shader{

    public:
    unsigned int program; //the program with linked shaders
    Shader();
    void use();
    void setMatrix(const std::string& name, const float* matrixPtr);
    void setVector(const std::string& name, float x, float y, float z, float w);
};