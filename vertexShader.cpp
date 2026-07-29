#include "vertexShader.h"
#include <GL/glew.h>
#include <iostream>

//CODE FOLLOWS THE LOGIC FROM THE ASSIGNMENT DOC + LAB#3

//we will make it take position and colour
static const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

uniform mat4 transform;
void main(){
gl_Position = transform * vec4(aPos, 1.0);
ourColor = aColor; 
}
)glsl";

//Lab3 code logic used for compilation of shader
//we have 2 shader types: fragment and vertex. Compile each separately and them link them together in Shader.cpp
unsigned int compileVertexShader(){
    
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);//compiling the shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compile error" << infoLog << std::endl;
    }
    return vertexShader;
}