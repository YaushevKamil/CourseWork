#include "include/window.hpp"

Window::Window(JSONConfig *config) : window_name(config->window_name),
                                     window_width(config->window_width),
                                     window_height(config->window_height),
                                     screen_width(config->screen_width),
                                     screen_height(config->screen_height),
                                     is_resizable(config->is_resizable) {}

bool Window::init() {
    if (glfwInit() != GL_TRUE) {
        std::cout << "ERROR::GLFW_INITIALIZATION_FAILED" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, is_resizable);

    window = glfwCreateWindow(window_width,
                              window_height,
                              window_name.c_str(),
                              nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "ERROR::FAILED_TO_CREATE_GLFW_WINDOW" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, (screen_width  - window_width)  / 2,
                     (screen_height - window_height) / 2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetErrorCallback(errorCallback);

    glewExperimental = GL_TRUE;
    GLint GlewInitResult = glewInit();
    bool err2 = (GlewInitResult != GLEW_OK);
    if (err2) {
        std::cout << "ERROR::GLEW_INITIALIZATION_FAILED" << std::endl;
        std::cout << glewGetErrorString(GlewInitResult) << std::endl;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    int view_port_width, view_port_height;
    glfwGetFramebufferSize(window, &view_port_width, &view_port_height);
    glViewport(0, 0, view_port_width, view_port_height);

    return true;
}

Window::~Window() {
    glfwTerminate();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    prefix_unused(window);
    glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* description) {
    std::cout << error << "::ERROR::" << description << std::endl;
}