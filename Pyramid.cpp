#include "Pyramid.h"
#include <GL/glew.h>


//logic found in lab+assignment document

// define buffer handles in this translation unit in case they're not
// declared in the header (prevents "no storage class or type specifier" errors)
unsigned int VAO, VBO, EBO;


Pyramid::Pyramid(){
    //Lab3 defined vertices with position and color, using the same logic here
    //pyramid has 6 apexes (square based pyramid), hence we need 6 coords

    //got the coordinates from Lab+online-- Possible to play around and change ratios
    float verticesPyramid[] = {
        // positions     colours
        - 0.5f, 0.0f, -0.5f,  1.0f, 0.0f, 0.0f, //#0
        0.5f, 0.0f, -0.5f,    0.0f, 1.0f, 0.0f, //#1
        0.5f, 0.0f, 0.5f,     0.0f, 0.0f, 1.0f, //#2
        - 0.5f, 0.0f, 0.5f,    1.0f, 1.0f, 0.0f, //#3
        0.0f, 0.7f, 0.0f,     1.0f, 1.0f, 1.0f //#4

    };
//Illustrating the "named" positions for each vertex of the pyramid. We will use these # for vertices

    //                               coord4.
    //                              /   /   .'
    //                          /      /      .'
    //                       /        /        . '
    //                   coord0  ----/------coord1.
    //                        ..    /               .'
    //                          .. /                  .'
    //                          coord3  -----------coord2
    // one is the apex, two are at the front, two are at the back. Out of them some are on the left/right

    unsigned int indices[]{
        //pyramid is made up of triangles: 4 triangles and a square base.
        //use coord# above to shape the triangles making up the pyramid
        //square base is made up of two triangles (1 square = 2 triangles)
        //in total we have 6 triangles defined here

        0,1,2, //triangle for square base 
        0,2,3, //triangle for square base
        0,1,4, //triangles
        1,2,4,
        2,3,4,
        3,0,4
    };

    //seting up the vertex array object VAO, vertex buffer object VBO and element buffer object EBO
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //bidn the vertex array object for the pyramid
    glBindVertexArray(VAO);
    //bind VBO 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPyramid), verticesPyramid, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

//Destructor
Pyramid::~Pyramid(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

//Draw pyramid
void Pyramid::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
