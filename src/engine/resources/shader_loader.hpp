#ifndef RESOURCES_SHADER_LOADER_HPP
#define RESOURCES_SHADER_LOADER_HPP

#include <fstream>
#include <string>

#include "../shading/shader.hpp"

namespace Engine {
    class ShaderLoader {
    public:
        static Shader Load(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defines = std::vector<std::string>());
    private:
        static std::string readShader(std::ifstream& file, const std::string& name, std::string path);
    };
}

#endif //RESOURCES_SHADER_LOADER_HPP