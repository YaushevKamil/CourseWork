#ifndef TABLE_HPP
#define TABLE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define EMPTY  0
#define PLAYER 1
#define GROUND 2
#define STAR   3
#define ENEMY  4

class Table {
public:
    Table(GLuint width, GLuint height);
    ~Table();
    void add(GLuint type, GLuint i, GLuint j);
    GLuint getType(GLuint i, GLuint j);
    friend std::ostream& operator<<(std::ostream& stream, Table& obj);

private:
    GLuint width;
    GLuint height;
    GLuint **arr;
};

#endif  // TABLE_HPP
