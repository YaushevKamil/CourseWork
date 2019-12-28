#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <string>

GLuint LoadTexture(std::string texture_name);
GLuint LoadCubeMapTexture(GLuint count, std::string* faces);

#endif  // TEXTURE_HPP