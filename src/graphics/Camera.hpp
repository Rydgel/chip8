#ifndef CHIP8_CAMERA_HPP
#define CHIP8_CAMERA_HPP

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

struct Camera
{
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
    ~Camera() = default;

    void update(const float dt);
    void processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = (GLboolean) true);
    void setupEvents();
    const GLfloat getZoom();
    const glm::vec3 getPosition();
    const glm::mat4 getViewMatrix();

private:

    bool firstMouseMove_ = true;
    GLfloat lastX_ = 400, lastY_ = 300;
    std::unordered_map<int, bool> keyStates_;

    // Camera attributes
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 worldUp_;
    // Eular Angles
    GLfloat yaw_;
    GLfloat pitch_;
    // Camera options
    GLfloat movementSpeed_;
    GLfloat mouseSensitivity_;
    GLfloat zoom_;

    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
    void updatePosition(const float dt);
    void updatePitch(const float dt);
    void updateZoom(const float dt);
};


#endif //CHIP8_CAMERA_HPP
