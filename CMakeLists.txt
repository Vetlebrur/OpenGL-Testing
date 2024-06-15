cmake_minimum_required(VERSION 3.10)

project(MyGLFWProject)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Find GLFW
find_package(glfw3 3.4 REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add the executable
add_executable(MyGLFWProject main.cpp)

# Link against GLFW and OpenGL
target_link_libraries(MyGLFWProject glfw OpenGL::GL)