#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <cmath>

enum class CameraDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    glm::vec3 position{0.0f, 0.0f, 3.5f};
    glm::vec3 front{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};
    glm::vec3 right{1.0f, 0.0f, 0.0f};
    const glm::vec3 worldUp{0.0f, 1.0f, 0.0f};

    float yaw{-90.0f};
    float pitch{0.0f};
    float speed{3.5f};
    float sensitivity{0.1f};

    Camera() {
        updateVectors();
    }

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    void processKeyboard(CameraDirection direction, float deltaTime) {
        float velocity = speed * deltaTime;
        if (direction == CameraDirection::FORWARD)  position += front * velocity;
        if (direction == CameraDirection::BACKWARD) position -= front * velocity;
        if (direction == CameraDirection::LEFT)     position -= right * velocity;
        if (direction == CameraDirection::RIGHT)    position += right * velocity;
    }

    void processMouseMovement(float xoffset, float yoffset) {
        yaw   += xoffset * sensitivity;
        pitch += yoffset * sensitivity;

        pitch = std::clamp(pitch, -85.0f, 85.0f);
        updateVectors();
    }

private:
    void updateVectors() {
        float radYaw = glm::radians(yaw);
        float radPitch = glm::radians(pitch);

        glm::vec3 newFront;
        newFront.x = std::cos(radYaw) * std::cos(radPitch);
        newFront.y = std::sin(radPitch);
        newFront.z = std::sin(radYaw) * std::cos(radPitch);
        front = glm::normalize(newFront);

        right = glm::normalize(glm::cross(front, worldUp));
        up    = glm::normalize(glm::cross(right, front));
    }
};