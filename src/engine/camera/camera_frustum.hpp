#ifndef CAMERA_FRUSTUM_HPP
#define CAMERA_FRUSTUM_HPP

#include "../math/math.hpp"

namespace Engine {
    class Camera;

    struct FrustumPlane {
        math::vec3 Normal;
        float D;

        void SetNormalD(math::vec3 normal, math::vec3 point) {
            Normal = math::normalize(normal);
            D = -math::dot(Normal, point);
        }

        float Distance(math::vec3 point) {
            return math::dot(Normal, point) + D;
        }
    };

    class CameraFrustum {
    public:
        struct planes {
            FrustumPlane Left;
            FrustumPlane Right;
            FrustumPlane Top;
            FrustumPlane Bottom;
            FrustumPlane Near;
            FrustumPlane Far;
            FrustumPlane& operator[](int i) { assert(i >= 0 && i < 6); return *(&Left+i); }
        } Planes;

    public:
        CameraFrustum() {}

        void Update(Camera* camera);

        bool Intersect(math::vec3 point);
        bool Intersect(math::vec3 point, float radius);
        bool Intersect(math::vec3 boxMin, math::vec3 boxMax);
    };
}

#endif //CAMERA_FRUSTUM_HPP