#include "include/input.hpp"

Camera* camera;
GLfloat lastMouseXOffset = 0.0f;
GLfloat lastMouseYOffset = 0.0f;

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

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    prefix_unused(window);
    prefix_unused(scanCode);
    prefix_unused(mods);

    if ((action == GLFW_PRESS) && (key >= 0) && (key < 1024)) {
        keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
    prefix_unused(window);

    if (firstMouse) {
        lastMouseXOffset = xPos;
        lastMouseYOffset = yPos;
        firstMouse = false;
    }

    GLfloat mouseXOffset = xPos - lastMouseXOffset;
    GLfloat mouseYOffset = lastMouseYOffset - yPos;

    lastMouseXOffset = xPos;
    lastMouseYOffset = yPos;

    camera->ProcessMouseMovement(mouseXOffset, mouseYOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    prefix_unused(window);
    prefix_unused(xOffset);

    camera->ProcessMouseScroll(yOffset);
}
