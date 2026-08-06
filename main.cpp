#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Pyramid.h"
#include "Shader.h"
#include "Transform.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> //we need this for the perspective and the lookAt()
#include <sstream> //to display the verification of transforms

bool isKeyPressed(GLFWwindow* window, int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}
void processInput(GLFWwindow* window, Transform& pyramidTransform)
{
    if (isKeyPressed(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);
    if (isKeyPressed(window, GLFW_KEY_W))
        pyramidTransform.translate({0, Transform::TRANSLATION_DISTANCE, 0});
    if (isKeyPressed(window, GLFW_KEY_S))
        pyramidTransform.translate({0, -Transform::TRANSLATION_DISTANCE, 0});
    if (isKeyPressed(window, GLFW_KEY_D))
        pyramidTransform.translate({Transform::TRANSLATION_DISTANCE, 0, 0});
    if (isKeyPressed(window, GLFW_KEY_A))
        pyramidTransform.translate({-Transform::TRANSLATION_DISTANCE, 0, 0});
    if (isKeyPressed(window, GLFW_KEY_Q))
        pyramidTransform.rotateAroundZ(Transform::ROTATION_STEP_DEGREES);
    if (isKeyPressed(window, GLFW_KEY_E))
        pyramidTransform.rotateAroundZ(-Transform::ROTATION_STEP_DEGREES);
    if (isKeyPressed(window, GLFW_KEY_R))
        pyramidTransform.scaleAlongZ(Transform::SCALE_FACTOR);
    if (isKeyPressed(window, GLFW_KEY_F))
        pyramidTransform.scaleAlongZ(1.0f / Transform::SCALE_FACTOR);
}
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
    

    // //////////////     CAMERA 

    // // VIEW MATRIX- we need it to know where the camera sits eye, up, at "target"
    // //glm::lookAt(eye, target, up)
    // glm::vec3 cameraPosition = glm::vec3(1.5f, 1.5f, 3.0f);
    // glm::vec3 cameraTarget   = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 upDirection    = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upDirection);

    // //Projection matrix glm::perspective(fovY, aspectRatio, near, far)
    // float fieldOfViewDegrees = 45.0f;
    // float aspect = 800.0f/600.0f;
    // float near= 0.1f;
    // float far = 100.0f;
    // glm::mat4 projection = glm::perspective(glm::radians(fieldOfViewDegrees), aspect, near, far);


    //RENDERING THE SHAPES---> loop all of the triangles rendering of Pyramid
    while (!glfwWindowShouldClose(window)){

        processInput(window, pyramidTransform);
        //Confirmt the transformations--make it visible to the user that stuff changed even if hard to see
        //used an external source to understand how to implement this to the window
        std::ostringstream title;
            title << "COMP371-A2 | translation: ("
          << pyramidTransform.translationValue().x << ", "
          << pyramidTransform.translationValue().y << ", "
          << pyramidTransform.translationValue().z << ") | rotation: "
          << pyramidTransform.rotationValue() << " deg | zScale: "
          << pyramidTransform.zScaleValue();
        glfwSetWindowTitle(window, title.str().c_str());
        //clear screen
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);//dark grey
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 transformMatrix = pyramidTransform.matrix();
        shader.setMatrix("transform", glm::value_ptr(transformMatrix)); //for the transforms

        //Setting the projection and the view to be able to see multiple pyramid sides (camera lookAt + fovY(...))
        // shader.setMatrix("view", glm::value_ptr(view));
        // shader.setMatrix("projection", glm::value_ptr(projection));
        //vertexShader.cpp also has a required gl_position line modified-- uncomment it for CAMERA
        
 

        pyramid.draw(); 

    

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

