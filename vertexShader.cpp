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
// Adding this to have a camera with a better perspective of the pyramid
uniform mat4 view;
uniform mat4 projection; //projection adds perspective

void main(){
// UNCOMMENT IF CAMERA gl_Position = projection * view * transform * vec4(aPos, 1.0); //view applies camera position, projection applies perspective OLD: gl_Position = transform * vec4(aPos, 1.0);
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