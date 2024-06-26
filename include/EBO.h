#ifndef EBO_CLASS_H //include guard
#define EBO_CLASS_H

#include "../include/glad/glad.h"

class EBO{
    public:
        GLuint ID;
        EBO(GLuint* indices, GLsizeiptr size);
        void Bind();
        void Unbind();
        void Delete();
};

#endif