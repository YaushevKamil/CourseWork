#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "def.hpp"
#include "json_config.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void errorCallback(int error, const char* description);

struct Window {
    Window(JSONConfig *config);
    ~Window();

    bool init();

    GLFWwindow* window;

    std::string window_name;
    GLuint window_width;
    GLuint window_height;
    GLuint screen_width;
    GLuint screen_height;
    bool is_resizable;
};

#endif // WINDOW_HPP