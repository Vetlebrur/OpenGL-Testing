#include <GLFW/glfw3.h>
#include "include/glad/glad.h"
#include <iostream>



constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f,0.7f,0.0f,1.0f);\n"
    "}\n\0";

int main() {

    //checks for glfw initialization
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    //creates window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "openGL testing", NULL, NULL);

    //checks for window creation
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //introdusce window into current context
    glfwMakeContextCurrent(window);

    //load glad to configure openGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //specifies viewport
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);


    //shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO,VBO; //VAO before VBO
    //VBO: Vertex buffer object
    //VAO: Vertex array object


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //binds buffer to array buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //copies vertices to buffer

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Specifies background color 
    glClearColor(0.0f,0.984f,1.0f,1.0f);
    //clears back buffer and assigns new color
    glClear(GL_COLOR_BUFFER_BIT);
    //swaps front and back buffer
    glfwSwapBuffers(window);

    //checks for window close,
    while (!glfwWindowShouldClose(window)) {//main loop
        
        //sets background colour
        glClearColor(0.0f,0.984f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draws a triangle
        glUseProgram(shaderProgram);  //selects shader program
        glBindVertexArray(VAO); //binds VAO
        glDrawArrays(GL_TRIANGLES,0,3); //draw


        //swaps front and back buffer
        glfwSwapBuffers(window);

        //polls all events
        glfwPollEvents();
    }

    //deletes VAO & VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteProgram(shaderProgram);

    //destroys window and terminates glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}