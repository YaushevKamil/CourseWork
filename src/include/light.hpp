#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

#include "shader.hpp"

class Light {
public:
    Light(glm::vec3 position,
          glm::vec4 ambient,
          glm::vec4 diffuse,
          glm::vec4 specular,
          Shader *terrain_shader,
          Shader *plane_shader,
          Shader *bot_shader);
    Light() = default;
private:
    static void Load(glm::vec3 position,
              glm::vec4 ambient,
              glm::vec4 diffuse,
              glm::vec4 specular,
              Shader *shader);
};

#endif // LIGHT_HPP