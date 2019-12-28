#ifndef INPUT_HPP
#define INPUT_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.hpp"
#include "def.hpp"

extern Camera *camera;

extern GLfloat last_mouse_xoffset;
extern GLfloat last_mouse_yoffset;

extern bool keys[1024];
extern bool firstMouse;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

struct Input {
public:
    Input(GLFWwindow* window, Camera* camera);
    void processInput(GLfloat* delta_time);
private:
    GLFWwindow* window;
};

#endif // INPUT_HPP