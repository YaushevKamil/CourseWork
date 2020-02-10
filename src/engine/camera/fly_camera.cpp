#include "fly_camera.hpp"

namespace Engine {
    FlyCamera::FlyCamera(math::vec3 position, math::vec3 forward, math::vec3 up) :
    Camera(position, forward, up), /*Yaw(-90.0f), Pitch(0.0f)*/Yaw(333.013f), Pitch(-36.8901f), m_WorldUp(Up), m_TargetPosition(position) {
        // TODO: delete forward, up vectors (use default values)
    }

    void FlyCamera::Update(float dt) {
        Camera::Update(dt);

        Position = math::lerp(Position, m_TargetPosition, math::clamp01(dt * Damping));
        Yaw      = math::lerp(Yaw, m_TargetYaw, math::clamp01(dt * Damping * 2.0f));
        Pitch    = math::lerp(Pitch, m_TargetPitch, math::clamp01(dt * Damping * 2.0f));

        math::vec3 newForward;
        newForward.x = cos(0.0174533 * Pitch) * cos(0.0174533 * Yaw);
        newForward.y = sin(0.0174533 * Pitch);
        newForward.z = cos(0.0174533 * Pitch) * sin(0.0174533 * Yaw);
        Forward = math::normalize(newForward);
        Right = math::normalize(math::cross(Forward, m_WorldUp));
        Up = math::cross(Right, Forward);

        UpdateView();
    }

    void FlyCamera::InputKey(float dt, CAMERA_MOVEMENT direction) {
        float speed = MovementSpeed * dt;
        if (direction      == CAMERA_FORWARD)
            m_TargetPosition = m_TargetPosition + Forward*speed;
        else if (direction == CAMERA_BACK)
            m_TargetPosition = m_TargetPosition - Forward*speed;
        else if (direction == CAMERA_LEFT)
            m_TargetPosition = m_TargetPosition - Right*speed;
        else if (direction == CAMERA_RIGHT)
            m_TargetPosition = m_TargetPosition + Right*speed;
        else if (direction == CAMERA_UP)
            m_TargetPosition = m_TargetPosition + m_WorldUp*speed;
        else if (direction == CAMERA_DOWN)
            m_TargetPosition = m_TargetPosition - m_WorldUp*speed;
    }

    void FlyCamera::InputMouse(float deltaX, float deltaY) {
        float xMovement = deltaX * MouseSensitivity;
        float yMovement = deltaY * MouseSensitivity;

        m_TargetYaw   += xMovement;
        m_TargetPitch += yMovement;

        if (m_TargetYaw == 0.0f) m_TargetYaw = 0.01f;
        if (m_TargetPitch == 0.0f) m_TargetPitch = 0.01f;

        if (m_TargetPitch > 89.0f)  m_TargetPitch =  89.0f;
        if (m_TargetPitch < -89.0f) m_TargetPitch = -89.0f;
    }

    float FlyCamera::GetYaw() {
        return Yaw;//m_TargetYaw;
    }

    float FlyCamera::GetPitch() {
        return Pitch;//m_TargetPitch;
    }
}