#include "include/input.hpp"

Camera* camera;
GLfloat last_mouse_xoffset = 0.0f;
GLfloat last_mouse_yoffset = 0.0f;

bool keys[1024];
bool firstMouse = true;

Input::Input(GLFWwindow* window, Camera* cam) : window(window) {
    camera = cam;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void Input::processInput(GLfloat* delta_time) {
    if (keys[GLFW_KEY_ESCAPE]) { glfwSetWindowShouldClose(window, GL_TRUE); }
    if (keys[GLFW_KEY_W]) { camera->ProcessKeyboard(FORWARD,  *delta_time); }
    if (keys[GLFW_KEY_S]) { camera->ProcessKeyboard(BACKWARD, *delta_time); }
    if (keys[GLFW_KEY_A]) { camera->ProcessKeyboard(LEFT,     *delta_time); }
    if (keys[GLFW_KEY_D]) { camera->ProcessKeyboard(RIGHT,    *delta_time); }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    prefix_unused(window);
    prefix_unused(scancode);
    prefix_unused(mods);

    if ((action == GLFW_PRESS) && (key >= 0) && (key < 1024)) {
        keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    prefix_unused(window);

    if (firstMouse) {
        last_mouse_xoffset = xpos;
        last_mouse_yoffset = ypos;
        firstMouse = false;
    }

    GLfloat mouse_xoffset = xpos - last_mouse_xoffset;
    GLfloat mouse_yoffset = last_mouse_yoffset - ypos;

    last_mouse_xoffset = xpos;
    last_mouse_yoffset = ypos;

    camera->ProcessMouseMovement(mouse_xoffset, mouse_yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    prefix_unused(window);
    prefix_unused(xoffset);

    camera->ProcessMouseScroll(yoffset);
}
