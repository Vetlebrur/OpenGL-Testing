#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "../include/glad/glad.h"
#include "/usr/local/include/GLFW/glfw3.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/glm/gtx/rotate_vector.hpp"
#include "../include/glm/gtx/vector_angle.hpp"

#include "shaderClass.h"



class Camera
{
    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f,0.0f,-1.0f);
        glm::vec3 Up = glm::vec3(0.0f,1.0f,0.0f);

        int width;
        int height;

        float speed = 0.1f;
        float sensitivity = 100.0f;

        Camera(int width, int height, glm::vec3 position);

        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
        void Inputs(GLFWwindow* window);
};

#endif