#include <math.h>

#include "camera.hpp"
#include "../math/trigonometry/conversions.hpp"

namespace Engine {
    Camera::Camera() {}

    Camera::Camera(math::vec3 position, math::vec3 forward, math::vec3 up) : Position(position), Forward(forward), Up(up) {
        UpdateView();
    }

    void Camera::Update(float dt) {
        Frustum.Update(this);
    }

    void Camera::SetPerspective(float fov, float aspect, float near, float far) {
        Perspective = true;
        Projection = math::perspective(fov, aspect, near, far);
        FOV    = fov;
        Aspect = aspect;
        Near   = near;
        Far    = far;
    }

    void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far) {
        Perspective = false;
        Projection = math::orthographic(left, right, top, bottom, near, far);
        Near = near;
        Far  = far;
    }

    void Camera::UpdateView() {
        math::vec3 Target = Position + Forward;
        View = math::lookAt(Position, Target, Up);
    }

    float Camera::FrustumHeightAtDistance(float distance) {
        if (Perspective) {
            return 2.0f * distance * tanf(math::Deg2Rad(FOV * 0.5));
        } else {
            return Frustum.Planes.Top.D;
        }
    }

    float Camera::DistanceAtFrustumHeight(float frustumHeight) {
        if (Perspective) {
            return frustumHeight * 0.5f / tanf(math::Deg2Rad(FOV * 0.5f));
        } else {
            return Frustum.Planes.Near.D;
        }
    }

    math::mat4 Camera::GetViewMatrix() {
        return View;
    }

    math::vec3 Camera::GetForwardVector() {
        return Forward;
    }

    math::vec3 Camera::GetPosition() {
        return Position;
    }

    math::vec3 Camera::GetUpVector() {
        return Up;
    }

    math::vec3 Camera::GetRightVector() {
        return Right;
    }
};