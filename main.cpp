#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Pyramid.h"
#include "Shader.h"
#include "Transform.h"
#include <glm/gtc/type_ptr.hpp>

int main(){

    //Init GLFW
    if (!glfwInit()){
        std::cerr<< "GLFW not initialized";
        return -1;
    }

    //opengl api
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create window with opengl context set above
    GLFWwindow* window = glfwCreateWindow(800, 600, "COMP371-A2", NULL, NULL);
    if (!window){
        std::cerr <<"No window created";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //INIT GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cerr<< "error init glew";
        return -1;
    }
    // consider depth bc the overlapping made the triangle fully white
    glEnable(GL_DEPTH_TEST);
   
    //Construct both shader and pyramid object
    Shader shader;
    Pyramid pyramid;

    
    // Step 3 Transform. 
    Transform pyramidTransform;
    
 
    //RENDERING THE SHAPES---> loop all of the triangles rendering of Pyramid
    while (!glfwWindowShouldClose(window)){
        //clear screen
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);//dark grey
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 transformMatrix = pyramidTransform.matrix();
        shader.setMatrix("transform", glm::value_ptr(transformMatrix));
 

        pyramid.draw(); 

    

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

