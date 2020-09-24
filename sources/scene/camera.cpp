//
// Created by Timothée Couble on 25/09/2020.
//

#include "camera.hpp"

using namespace scene;

Camera::Camera() {
    updateCamerasVectors();
}

void Camera::updateCamerasVectors() {
    m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_worldUp));
    m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
}


const glm::vec3 &Camera::getCameraPosition() const {
    return m_cameraPos;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

glm::mat4 Camera::getProjectionMatrix(float ratio) const {
    auto projection = glm::perspective(glm::radians(m_fov), ratio, 0.1f, 50.0f);
    projection[1][1] *= -1;
    return projection;
}

void Camera::zoom(double yOffset) {
    m_fov -= (float) yOffset / 2;
    if (m_fov <= 1.0f)
        m_fov = 1.0f;
    else if (m_fov >= 45.0f)
        m_fov = 45.0f;
}

void Camera::moveForward() {
    m_cameraPos += m_cameraFront * m_cameraSpeed;
}

void Camera::moveBackward() {
    m_cameraPos -= m_cameraFront * m_cameraSpeed;
}

void Camera::moveUp() {
    m_cameraPos += m_cameraUp * m_cameraSpeed;
}

void Camera::moveDown() {
    m_cameraPos -= m_cameraUp * m_cameraSpeed;
}

void Camera::moveLeft() {
    m_cameraPos -= m_cameraRight * m_cameraSpeed;
}

void Camera::moveRight() {
    m_cameraPos += m_cameraRight * m_cameraSpeed;
}

void Camera::rotateLeft() {
    m_cameraFront = glm::angleAxis(m_cameraSpeed / 6, m_cameraUp) * m_cameraFront;
    updateCamerasVectors();
}

void Camera::rotateRight() {
    m_cameraFront = glm::angleAxis(-m_cameraSpeed / 6, m_cameraUp) * m_cameraFront;
    updateCamerasVectors();
}