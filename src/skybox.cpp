#include "include/skybox.hpp"

Skybox::Skybox(GLuint texture, Shader *shader) :
        VAO(0), VBO(0), EBO(0),
        texture(texture),
        shader(shader) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    GLfloat boxVertices[] = {
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), &boxVertices, GL_STATIC_DRAW);

    GLuint boxIndices[] = {
            0, 1, 2, 3, 4, 5,
            5, 3, 6, 1, 7, 0,
            0, 2, 7, 4, 6, 5
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), &boxIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (GLvoid*)(0*sizeof(GLfloat)));

    glBindVertexArray(0);
}

Skybox::~Skybox() {
    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);

    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
}

void Skybox::draw() {
    GLint oldCullFaceMode;
    GLint oldDepthFuncMode;

    glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
    glGetIntegerv(GL_DEPTH_FUNC,     &oldDepthFuncMode);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    shader->use();

    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    shader->unUse();

    glCullFace(oldCullFaceMode);
    glDepthFunc(oldDepthFuncMode);
}
