#include "include/camera.hpp"

const GLfloat YAW         = -90.0f;
const GLfloat PITCH       =  0.0f;
const GLfloat SPEED       =  10;
const GLfloat SENSITIVITY =  0.1f;
const GLfloat ZOOM        =  45.0f;

Camera::Camera(GLint window_width,
               GLint window_height,
               glm::vec3 position,
               Shader *terrain_shader,
               Shader *bot_shader,
               Shader *plane_shader,
               Shader *skybox_shader) :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY),
        Zoom(ZOOM) {
    this->window_width  = window_width;
    this->window_height = window_height;
    this->Pitch = PITCH;
    this->Yaw = YAW;
    this->Position = position;
    this->terrain_shader = terrain_shader;
    this->bot_shader = bot_shader;
    this->plane_shader = plane_shader;
    this->skybox_shader = skybox_shader;
    this->tangent = (float)window_width / (float)window_height;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
    GLfloat velocity = MovementSpeed * deltaTime;
    switch (direction) {
        case FORWARD :
            Position += Front * velocity;
            break;
        case BACKWARD :
            Position -= Front * velocity;
            break;
        case LEFT :
            Position -= Right * velocity;
            break;
        case RIGHT :
            Position += Right * velocity;
            break;
    }
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (Pitch >  89.0f) Pitch =  89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset) {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)  Zoom = 1.0f;
    if (Zoom >= 45.0f) Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

void Camera::updateViewProjMatrix() {
    uniform(terrain_shader);
    uniform(bot_shader);
    uniform(plane_shader);
    uniform(skybox_shader, true);
}

void Camera::uniform(Shader* shader, bool isSkybox) {
    glm::mat4 view = GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(Zoom), tangent, 0.1f, 500.0f);
    if (isSkybox) view = glm::mat4(glm::mat3(view));

    shader->use();
    glUniformMatrix4fv(shader->getUniLoc("view"),       1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader->getUniLoc("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    if (!isSkybox) glUniform3fv(shader->getUniLoc("viewPos"), 1, glm::value_ptr(Position));
}