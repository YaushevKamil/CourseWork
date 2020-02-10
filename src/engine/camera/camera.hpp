#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "camera_frustum.hpp"
#include "../math/math.hpp"

namespace Engine {
    enum CAMERA_MOVEMENT {
        CAMERA_FORWARD,
        CAMERA_BACK,
        CAMERA_LEFT,
        CAMERA_RIGHT,
        CAMERA_UP,
        CAMERA_DOWN,
    };

    class Camera {
    public:
        math::mat4 Projection;
        math::mat4 View;

        math::vec3 Position = math::vec3(0.0f, 0.0f,  0.0f);
        math::vec3 Forward  = math::vec3(0.0f, 0.0f, -1.0f);
        math::vec3 Up       = math::vec3(0.0f, 1.0f,  0.0f);
        math::vec3 Right    = math::vec3(1.0f, 0.0f,  0.0f);

        float FOV;
        float Aspect;
        float Near;
        float Far;
        bool  Perspective;

        CameraFrustum Frustum;
    private:
    public:
        Camera();
        Camera(math::vec3 position, math::vec3 forward, math::vec3 up);

        virtual void Update(float dt);

        void SetPerspective(float fov, float aspect, float near, float far);
        void SetOrthographic(float left, float right, float top, float bottom, float near, float far);

        void UpdateView();

        math::mat4 GetViewMatrix();
        math::vec3 GetPosition();
        math::vec3 GetForwardVector();
        math::vec3 GetUpVector();
        math::vec3 GetRightVector();

        float FrustumHeightAtDistance(float distance);
        float DistanceAtFrustumHeight(float frustumHeight);
    };
}

#endif //CAMERA_HPP