#ifndef SHADING_SHADER_HPP
#define SHADING_SHADER_HPP

#include <string>
#include <vector>

#include "shading_types.hpp"
#include "../glad/glad.h"
#include "../utility/logging/log.hpp"

namespace Engine {
    class Shader {
    public:
        unsigned int ID;
        std::string  Name;

        std::vector<Uniform>         Uniforms;
        std::vector<VertexAttribute> Attributes;

    public:
        Shader();
        Shader(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines = std::vector<std::string>());

        void Load(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines = std::vector<std::string>());

        void Use();

        bool HasUniform(std::string name);

        void SetInt   (std::string location, int   value);
        void SetBool  (std::string location, bool  value);
        void SetFloat (std::string location, float value);
        void SetVector(std::string location, math::vec2  value);
        void SetVector(std::string location, math::vec3  value);
        void SetVector(std::string location, math::vec4  value);
        void SetVectorArray(std::string location, int size, const std::vector<math::vec2>& values);
        void SetVectorArray(std::string location, int size, const std::vector<math::vec3>& values);
        void SetVectorArray(std::string location, int size, const std::vector<math::vec4>& values);
        void SetMatrix(std::string location, math::mat2 value);
        void SetMatrix(std::string location, math::mat3 value);
        void SetMatrix(std::string location, math::mat4 value);
        void SetMatrixArray(std::string location, int size, math::mat2* values);
        void SetMatrixArray(std::string location, int size, math::mat3* values);
        void SetMatrixArray(std::string location, int size, math::mat4* values);
    private:
        int getUniformLocation(std::string name);
    };
}

#endif //SHADING_SHADER_HPP