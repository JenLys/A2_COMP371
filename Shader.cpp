#include "Shader.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include <GL/glew.h>
#include <iostream>


//Responsible for linking both fragment and vertex shaders. Once linked, remove the individual instances of each
Shader::Shader(){
    unsigned int vertexShader = compileVertexShader();
    unsigned int fragmentShader = compileFragmentShader();

    //Call on the compilation of each kind of shader individually, attach them to a created shader program (common to both)
program = glCreateProgram();
glAttachShader(program, vertexShader);
glAttachShader(program, fragmentShader);

//link it to GPU since that's the thing shaders act on to get graphics displayed
glLinkProgram(program);

//a little sanity check + error handling in case something fails
int success;
glGetProgramiv(program, GL_LINK_STATUS, &success);

if (!success){
    char infoLog[512];
    glGetProgramInfoLog(program, 5012, NULL, infoLog);
    std::cerr << "Shader linking problem" << infoLog <<std::endl;
}

//two shader types linked together, remove previous individual shaders (only keep the linked version of the two)
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
}

//to use the shader program defined with both shader types
void Shader::use() {
    glUseProgram(program);
}

//setters
void Shader::setMatrix(const std::string& name, const float* matrixPtr){
    int location = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, matrixPtr);
}
void Shader::setVector(const std::string& name, float x, float y, float z, float w){
    int location = glGetUniformLocation(program, name.c_str());
    glUniform4f(location, x, y, z, w);
}


