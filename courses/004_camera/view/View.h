#pragma once
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <functional>


class View {

public:
    View(int width, int height);
    ~View();
    bool init();
	//Set event callback
    void setGLFWCallback(std::function<void(int)>){};
    bool shouldClose(){return glfwWindowShouldClose(_window);};
    void clear();
    void swap();
	GLFWwindow* getWindow() { return _window; }
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;
private:
    GLFWwindow* _window;
    int _height;
    int _width;
};
