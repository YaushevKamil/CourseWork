#ifndef RENDERER_RENDER_COMMAND_HPP
#define RENDERER_RENDER_COMMAND_HPP

#include "../math/math.hpp"

namespace Engine {
    class Mesh;
    class Material;

    struct RenderCommand {
        math::mat4 c_Transform;
        math::mat4 c_PrevTransform;
        Mesh*      c_Mesh;
        Material*  c_Material;
        math::vec3 c_BoxMin;
        math::vec3 c_BoxMax;
    };
}

#endif //RENDERER_RENDER_COMMAND_HPP
