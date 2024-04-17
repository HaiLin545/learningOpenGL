//
// Created by 16064 on 2024/04/15.
//

#ifndef LEARNINGOPENGL_CAMERA_HPP
#define LEARNINGOPENGL_CAMERA_HPP

#include "head.hpp"

enum CAMERA_MOVE {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_SPEED = 2.5f;
const float DEFAULT_SENSITIVITY = 0.1f;
const float DEFAULT_FOV = 45.0f;
const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 DEFAULT_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 DEFAULT_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);

class Camera {
public:
    glm::vec3 Position, Front, Right, Up, WorldUp;
    float Yaw, Pitch, Speed, Sensitivity, Fov;

    Camera(glm::vec3 position = DEFAULT_POSITION, glm::vec3 up = DEFAULT_UP, float yaw = DEFAULT_YAW,
           float pitch = DEFAULT_PITCH) : Yaw(yaw), Pitch(pitch), WorldUp(up), Position(position) {
        Front = DEFAULT_FRONT;
        Speed = DEFAULT_SPEED;
        Sensitivity = DEFAULT_SENSITIVITY;
        Fov = DEFAULT_FOV;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(CAMERA_MOVE dir, float deltaTime) {
        float velocity = Speed * deltaTime;
        if (dir == FORWARD) {
            Position += Front * velocity;
        } else if (dir == BACKWARD) {
            Position -= Front * velocity;
        } else if (dir == RIGHT) {
            Position += Right * velocity;
        } else if (dir == LEFT) {
            Position -= Right * velocity;
        }
    }

    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true) {

        xOffset *= Sensitivity;
        yOffset *= Sensitivity;
        Yaw += xOffset;
        Pitch += yOffset;
        if (constrainPitch) {
            if (Pitch > 89.0f)Pitch = 89.0f;
            if (Pitch < -89.0f)Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yOffset) {
        Fov -= yOffset;
        if (Fov < 1.0f)Fov = 1.0f;
        if (Fov > 45.0f)Fov = 45.0f;
    }

private:

    void updateCameraVectors() {
        glm::vec3 front;
        front.y = sin(glm::radians(Pitch));
        front.x = cos(glm::radians((Pitch))) * cos(glm::radians(Yaw));
        front.z = cos(glm::radians((Pitch))) * sin(glm::radians((Yaw)));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }

};

#endif //LEARNINGOPENGL_CAMERA_HPP
