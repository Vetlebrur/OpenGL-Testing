#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "../include/glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>

class VBO{
    public:
        GLuint ID;
        VBO(GLfloat* vertices, GLsizeiptr size);
        void Bind();
        void Unbind();
        void Delete();
};

#endif