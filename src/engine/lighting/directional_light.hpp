#ifndef LIGHTING_DIRECTIONAL_LIGHT_HPP
#define LIGHTING_DIRECTIONAL_LIGHT_HPP

#include "../math/math.hpp"

namespace Engine {
    class RenderTarget;

    class DirectionalLight {
    public:
        math::vec3 Direction = math::vec3(0.0f);
        math::vec3 Color = math::vec3(1.0f);
        float Intensity = 1.0f;

        bool CastShadows = true;
        RenderTarget* ShadowMapRT = nullptr;
        math::mat4 LightSpaceViewProjection;
    };
}

#endif //LIGHTING_DIRECTIONAL_LIGHT_HPP