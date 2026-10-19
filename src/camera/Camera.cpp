#include "Camera.hpp"

Camera::Camera()
    : Camera(
        Vec3(0.0f, 0.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        YAW,
        PITCH
    )
{}

Camera::Camera(
    Vec3 position, Vec3 up,
    float yaw, float pitch
)
    : MovementSpeed(SPEED),
    Zoom(ZOOM),
    Position(position),
    WorldUp(up),
    Yaw(yaw), Pitch(pitch),
    isSprinting(false),
    orbitTarget(),
    orbitDistance(3.0f),
    maxOrbitDistance(15.0f)
{
    updateCameraVectors();

    orbitDistance = std::max(0.1f, (Position - orbitTarget).length());
    maxOrbitDistance = orbitDistance * 3.0f;
    updateOrbitPosition();
}

Mat4 Camera::GetViewMatrix() const
{
    return Mat4::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    switch (direction)
    {
        case SPRINT_ON:
            isSprinting = true;
            return;
        case SPRINT_OFF:
            isSprinting = false;
            return;
        default:
            break;
    }

    const float velocity = MovementSpeed * deltaTime
        * (isSprinting ? SPRINT : 1.0f);

    switch (direction)
    {
        case FORWARD:
            orbitDistance = std::max(0.1f, orbitDistance - velocity);
            break;
        case BACKWARD:
            orbitDistance = std::min(maxOrbitDistance, orbitDistance + velocity);
            break;
        case LEFT:
            Yaw -= velocity * 20.0f;
            break;
        case RIGHT:
            Yaw += velocity * 20.0f;
            break;
        case UP:
            Pitch += velocity * 20.0f;
            break;
        case DOWN:
            Pitch -= velocity * 20.0f;
            break;
        default:
            return;
    }

    Pitch = std::clamp(Pitch, -89.0f, 89.0f);
    updateCameraVectors();
    updateOrbitPosition();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    const float zoomStep = 0.75f;
    orbitDistance = std::clamp(orbitDistance - yoffset * zoomStep,
                              0.1f, maxOrbitDistance);
    updateOrbitPosition();
}

void Camera::updateCameraVectors()
{
    Vec3 front;
    const float rYaw = Math::radians(Yaw);
    const float rPitch = Math::radians(Pitch);

    front.x = cos(rYaw) * cos(rPitch);
    front.y = sin(rPitch);
    front.z = sin(rYaw) * cos(rPitch);
    Front   = front.normalize();

    Right = Front.cross(WorldUp).normalize();
    Up    = Right.cross(Front).normalize();
}

void Camera::updateOrbitPosition()
{
    Position = orbitTarget - Front * orbitDistance;
}

