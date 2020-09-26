//
// Created by Timothée Couble on 25/09/2020.
//

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <memory>

#include "libraries.hpp"

namespace scene {

    /**
     * Camera handler class which used in Echess.
     */
    class Camera {
    public:
        Camera();

        const glm::vec3 &getCameraPosition() const;
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix(float ratio) const;

        void zoom(double yOffset);

        void moveForward();
        void moveBackward();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void rotateLeft();
        void rotateRight();

    private:
        void updateCamerasVectors();

    private:
        float m_fov = 45.0f;

        glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, -4.0f);
        glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_cameraRight = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        const float m_cameraSpeed = 0.1f;
    };

    typedef std::unique_ptr<Camera> Camera_ptr_t;
    typedef void (scene::Camera::*change_camera_t)();

}

#endif /* !CAMERA_HPP */
