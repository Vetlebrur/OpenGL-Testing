#include <GLFW/glfw3.h>
#include "include/glad/glad.h"
#include <iostream>

#include "include/shaderClass.h"
#include "include/VAO.h"
#include "include/VBO.h"
#include "include/EBO.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

int main() {

    //checks for glfw initialization
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //vertices coordinates
    GLfloat vertices[] = {
        -0.5f, -0.5f*float(sqrt(3))/3, 0.0f, 0.8f, 0.3f, 0.02f,
        0.5f, -0.5f*float(sqrt(3))/3, 0.0f, 0.8f, 0.3f, 0.02f,
        0.0f,  0.5f*float(sqrt(3))*2/3, 0.0f, 1.0f, 0.6f, 0.32f,
        -0.5f/2, 0.5f*float(sqrt(3))/6, 0.0f, 0.9f, 0.45f, 0.17f,
        0.5f/2, 0.5f*float(sqrt(3))/6, 0.0f, 0.9f, 0.45f, 0.17f,
        0.0f/2, -0.5f*float(sqrt(3))/3, 0.0f, 0.8f, 0.3f, 0.02f,

    };

    GLuint indices[] = 
    {
        0,3,5,
        3,2,4,
        5,4,1
    };

    //creates window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "openGL testing", NULL, NULL);

    //checks for window creation
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //introduce window into current context
    glfwMakeContextCurrent(window);

    //load glad to configure openGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //specifies viewport
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

    Shader shaderProgram("shaders/default.vert","shaders/default.frag");
 
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(indices,sizeof(indices));

    VAO1.LinkAttrib(VBO1,0,3,GL_FLOAT,6*sizeof(float),(void*)0);
    VAO1.LinkAttrib(VBO1,1,3,GL_FLOAT,6*sizeof(float),(void*)(3*sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
  

    //checks for window close,
    while (!glfwWindowShouldClose(window)) {//main loop
        
        //sets background colour
        glClearColor(1.0f,0.4f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draws a triangle
        shaderProgram.Activate();  //selects shader program
        
        //binds VAO s.t. openGL knows to use it
        VAO1.Bind();
        
        //glDrawArrays(GL_TRIANGLES,0,3); //Use if only drawing one triangle
        //draws all elements
        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);


        //swaps front and back buffer
        glfwSwapBuffers(window);

        //polls all events
        glfwPollEvents();
    }

    //deletes VAO & VBO
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    //destroys window and terminates glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}