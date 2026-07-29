#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
   

    //MAIN
    while (!glfwWindowShouldClose(window)){
        //clear screen
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //RENDERING CODE FOR THE PYRAMID GOES HERE

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

