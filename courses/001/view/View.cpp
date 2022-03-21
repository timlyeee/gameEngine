#include "View.h"
#include "GLFW/glfw3.h"
#include "GLFWCallback.cpp"
#include <iostream>

View::View(int width, int height){
    _height = height;
    _width = width;
}
View::~View(){
    glfwTerminate();
}

//return if the window is successfully init
bool View::init(){
    //glew init
    
    
    //init opengl context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = glfwCreateWindow(_width, _height, "GL Case", NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(_window);
    
    //set callbacks
    glfwSetFramebufferSizeCallback(_window, frameBuffer_size_callback);
    glViewport(0, 0, _width, _height);
    return true;
}

void View::clear(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void View::swap(){
    glfwSwapBuffers(_window);
    glfwPollEvents();
}
