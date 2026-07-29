#include "fragmentShader.h"
#include <GL/glew.h>
#include <iostream>

//CODE FOLLOWS THE LOGIC FROM THE ASSIGNMENT DOC + LAB#3

//from assignment description
static const char* fragmentShaderSource = R"glsl(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main(){
FragColor = vec4(ourColor, 1.0);
}
)glsl";

//Lab3 code logic used for compilation of shader
//we have 2 shader types: fragment and vertex. Compile each separately and them link them together in Shader.cpp
unsigned int compileFragmentShader(){
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//compiling the shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    int success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "fragment shader compile error" << infoLog << std::endl;
    }
    return fragmentShader;
}