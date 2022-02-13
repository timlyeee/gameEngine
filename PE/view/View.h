#pragma once
#include <GLFW/glfw3.h>
#include <functional>
class View {

public:
    View(int width, int height);
    ~View();
    bool init();
    void setGLFWCallback(std::function<void(int)>){};
    bool shouldClose(){return glfwWindowShouldClose(_window);};
    void renderLoop();
private:
    GLFWwindow* _window;
    int _height;
    int _width;
};
