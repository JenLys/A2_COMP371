#pragma once

class Pyramid{

    private: //vertex array object, vertex buffer object, and element buffer object
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    public:
    Pyramid();
    ~Pyramid();
    void draw();
};