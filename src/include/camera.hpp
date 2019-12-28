#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

extern const GLfloat YAW;
extern const GLfloat PITCH;
extern const GLfloat SPEED;
extern const GLfloat SENSITIVITY;
extern const GLfloat ZOOM;

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    GLfloat Yaw;
    GLfloat Pitch;

    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

    GLint window_width;
    GLint window_height;

    Camera(GLint window_width,
           GLint window_height,
           glm::vec3 position,
           Shader* terrain_shader,
           Shader* bot_shader,
           Shader* plane_shader,
           Shader* skybox_shader);
    Camera() = default;

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
    void ProcessMouseScroll(GLfloat yoffset);
    void updateViewProjMatrix();

private:
    GLfloat tangent;

    Shader* terrain_shader;
    Shader* bot_shader;
    Shader* plane_shader;
    Shader* skybox_shader;

    void updateCameraVectors();
    void uniform(Shader* shader, bool isSkybox = false);
};

#endif // CAMERA_HPP