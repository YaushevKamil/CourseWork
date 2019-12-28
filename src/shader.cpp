#include "include/shader.hpp"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    char infoLog[512];
    GLuint vertexShader, fragmentShader = 0;

    id = glCreateProgram();

    vertexShader = compile(vertexPath, GL_VERTEX_SHADER, infoLog);
    glAttachShader(id, vertexShader);

    fragmentShader = compile(fragmentPath, GL_FRAGMENT_SHADER, infoLog);
    glAttachShader(id, fragmentShader);

    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::compile(const std::string& path, GLenum type, char *infoLog) {
    GLuint shader = glCreateShader(type);
    std::ifstream source;
    source.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        source.open(path);
        std::stringstream stream;
        stream << source.rdbuf();
        source.close();
        std::string str = stream.str();
        const char* charStr = str.c_str();
        glShaderSource(shader, 1, &charStr, nullptr);
        glCompileShader(shader);
    } catch (const std::ifstream::failure &e) {
        std::cout << "CAUGHT_ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << e.what() << std::endl;
    }

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::" << (
                type == GL_VERTEX_SHADER ?
                "VERTEX"   :
                "FRAGMENT"
            );
        std::cout << "::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
    }
    return shader;
}
