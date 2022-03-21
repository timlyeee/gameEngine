#include "View.h"
#include "GLFW/glfw3.h"
#include "GLFWCallback.cpp"
#include <iostream>
bool firstMouse{ true };
float lastX = 480, lastY = 320;
float yaw = -90.f, pitch = 0.f;
glm::vec3 View::cameraPos{ glm::vec3(0.0f, 0.0f, 3.0f) };
glm::vec3 View::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 View::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
View::View(int width, int height){
    _height = height;
    _width = width;
}
View::~View(){
    glfwTerminate();
}
void View::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	View::cameraFront = glm::normalize(front);
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
	glfwSetCursorPosCallback(_window, mouse_callback);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
