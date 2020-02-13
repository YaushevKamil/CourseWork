#ifndef LIGHTING_POINT_LIGHT_HPP
#define LIGHTING_POINT_LIGHT_HPP

#include "../math/math.hpp"

#include "../shading/material.hpp"
#include "../mesh/sphere.hpp"

namespace Engine {
    class PointLight {
    public:
        math::vec3 Position   = math::vec3(0.0f);
        math::vec3 Color      = math::vec3(1.0f);
        float      Intensity  = 1.0f;
        float      Radius     = 1.0f;
        bool       Visible    = true;
        bool       RenderMesh = false;
    };
}

#endif //LIGHTING_POINT_LIGHT_HPP
