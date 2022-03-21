#include "View.h"
#include "GLFWCallback.h"
#include <iostream>

Camera View::camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

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
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
	glfwSetCursorPosCallback(_window, mouse_callback);
	glfwSetScrollCallback(_window, scroll_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glViewport(0, 0, _width, _height);
    return true;
}

void View::clear() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void View::swap(){
    glfwSwapBuffers(_window);
    
}
