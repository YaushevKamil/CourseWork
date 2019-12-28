#ifndef INPUT_HPP
#define INPUT_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.hpp"
#include "def.hpp"

extern Camera *camera;

extern GLfloat lastMouseXOffset;
extern GLfloat lastMouseYOffset;

extern bool keys[1024];
extern bool firstMouse;

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

struct Input {
public:
    Input(GLFWwindow* window, Camera* camera);
    void processInput(GLfloat* delta_time);
private:
    GLFWwindow* window;
};

#endif // INPUT_HPP