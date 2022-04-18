#pragma once
#include <GLFW/glfw3.h>
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
private:
    GLFWwindow* _window;
    int _height;
    int _width;
};
