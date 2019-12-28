#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "shader.hpp"

class Skybox {
public:
    Skybox(GLuint texture, Shader* shader);
    ~Skybox();
    void draw();
private:
    GLuint  VAO;
    GLuint  VBO;
    GLuint  EBO;
    GLuint  texture;
    Shader* shader;
};

#endif // SKYBOX_HPP