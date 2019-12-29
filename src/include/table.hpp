#ifndef TABLE_HPP
#define TABLE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define PLAYER 0
#define GROUND 1
#define STAR   2
#define ENEMY  3

class Table {
public:
    Table(GLuint width, GLuint height);
    ~Table();
    void add(GLuint type, GLuint i, GLuint j);
    GLuint getType(GLuint i, GLuint j);
    void print();

private:
    GLuint width;
    GLuint height;
};

#endif  // TABLE_HPP
