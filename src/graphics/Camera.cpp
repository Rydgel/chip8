#include <GLFW/glfw3.h>
#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
: front_(glm::vec3(0.0f, 0.0f, -10.0f))
, movementSpeed_(SPEED)
, mouseSensitivity_(SENSITIVITY)
, zoom_(ZOOM)
{
    position_ = position;
    worldUp_ = up;
    yaw_ = yaw;
    pitch_ = pitch;

    updateCameraVectors();
    setupEvents();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw,
               GLfloat pitch)
: front_(glm::vec3(0.0f, 0.0f, -10.0f))
, movementSpeed_(SPEED)
, mouseSensitivity_(SENSITIVITY)
, zoom_(ZOOM)
{
    position_ = glm::vec3(posX, posY, posZ);
    worldUp_ = glm::vec3(upX, upY, upZ);
    yaw_ = yaw;
    pitch_ = pitch;

    updateCameraVectors();
    setupEvents();
}

void Camera::updatePosition(const float dt)
{
    // todo
    GLfloat velocity = movementSpeed_ * dt;
    if (keyStates_[GLFW_KEY_W])
        position_ += front_ * velocity;
    if (keyStates_[GLFW_KEY_S])
        position_ -= front_ * velocity;
    if (keyStates_[GLFW_KEY_A])
        position_ -= right_ * velocity;
    if (keyStates_[GLFW_KEY_D])
        position_ += right_ * velocity;
    if (keyStates_[GLFW_KEY_SPACE])
        position_.y += velocity;
    if (keyStates_[GLFW_KEY_LEFT_CONTROL])
        position_.y -= velocity;
}

void Camera::updatePitch(const float dt)
{

}

void Camera::updateZoom(const float dt)
{

}

void Camera::update(const float dt)
{
    updatePosition(dt);
    // Update Front, Right and Up Vectors using the updated Eular angles
    updateCameraVectors();
}

void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity_;
    yoffset *= mouseSensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }
}

const GLfloat Camera::getZoom()
{
    return zoom_;
}

const glm::vec3 Camera::getPosition()
{
    return position_;
}

const glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cosf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));
    front.y = sinf(glm::radians(pitch_));
    front.z = sinf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));
    front_ = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_ = glm::normalize(glm::cross(right_, front_));
}

void Camera::setupEvents()
{
    // todo dododdo?
}
