#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader{
private:
    GLuint id;
public:
    Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");

    GLuint getID() const  { return id; };
    GLint  getUniLoc(const char *name) const  { return glGetUniformLocation(id, name); };
    GLint  getAttrLov(const char *name) const { return glGetAttribLocation( id, name); };

    void use() const { glUseProgram(id); }
    void unUse()     { glUseProgram(0);  }
    void destroy()   { glDeleteProgram(id); };
private:
    GLuint compile(std::string path, GLenum type, char *infoLog);
};

#endif //SHADER_HPP
