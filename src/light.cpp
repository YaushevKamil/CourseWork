#include "include/light.hpp"

Light::Light(glm::vec3 position,
             glm::vec4 ambient,
             glm::vec4 diffuse,
             glm::vec4 specular,
             Shader *terrain_shader,
             Shader *plane_shader,
             Shader *bot_shader) {
    position = -position;
    Load(position, ambient, diffuse, specular, terrain_shader);
    Load(position, ambient, diffuse, specular, plane_shader);
    Load(position, ambient, diffuse, specular, bot_shader);
}

void Light::Load(glm::vec3 position,
                 glm::vec4 ambient,
                 glm::vec4 diffuse,
                 glm::vec4 specular,
                 Shader *shader) {
    shader->use();
    glUniform3fv(shader->getUniLoc("light.direction"), 1, &position[0]);
    glUniform3fv(shader->getUniLoc("lightDir"), 1, &position[0]);
    glUniform4fv(shader->getUniLoc("light.ambient"),   1, &ambient [0]);
    glUniform4fv(shader->getUniLoc("light.diffuse"),   1, &diffuse [0]);
    glUniform4fv(shader->getUniLoc("light.specular"),  1, &specular[0]);
}