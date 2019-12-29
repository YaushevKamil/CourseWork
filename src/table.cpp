#include "include/table.hpp"

Table::Table(GLuint width, GLuint height) :
        width(width), height(height) {
    arr = new GLuint* [width];
    for (GLuint i = 0; i < width; i++) {
        arr[i] = new GLuint[height];
        for (GLuint j = 0; j < height; j++) {
            arr[i][j] = EMPTY;
        }
    }
}

Table::~Table() {
    for (GLuint i = 0; i < width; i++) {
        delete [] arr[i];
    }
    delete arr;
}

void Table::add(GLuint type, GLuint i, GLuint j) {
    if (type != PLAYER && type != GROUND && type != STAR && type != ENEMY) {
        std::cout << "ERROR::TABLE::UNKNOWN_TYPE" << std::endl;
        return;
    }
    arr[i][j] = type;
}

GLuint Table::getType(GLuint i, GLuint j) {
    return arr[i][j];
}

std::ostream& operator<<(std::ostream& stream, Table& obj) {
    stream << std::endl;
    stream << "--------------";
    for (GLuint i = 0; i < obj.width; i++) {
        for (GLuint j = 0; j < obj.height; j++) {
            switch (obj.arr[i][j]) {
                case PLAYER:
                    stream << "P ";
                    break;
                case GROUND:
                    stream << "G ";
                    break;
                case STAR:
                    stream << "S ";
                    break;
                case ENEMY:
                    stream << "X ";
                    break;
                default:
                    stream << "  ";
            }
        }
    }
    stream << "--------------";
    stream << std::endl;
}
