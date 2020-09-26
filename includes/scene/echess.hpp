//
// Created by Timothée Couble on 25/09/2020.
//

#ifndef ECHESS_HPP
# define ECHESS_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include "application.hpp"
#include "camera.hpp"
#include "pawn.hpp"

namespace scene {

    /**
     * Scene handler class that inherit from Application.
     * Handle scene models and events.
     */
    class Echess : public vk_wrapper::Application {
    public:
        Echess();

    private:
        void initModels() override;

        void onDraw() override;

        void checkKey();

        void onMouseMove(double x, double y) final;
        void onMouseDown(int button, int action) final;
        void onMouseScroll(double x, double y) final;
        void onKeyDown(int key, int action) final;

    private:
        bool m_pressed = false;
        bool m_keyCode[512] = {false};
        Camera_ptr_t m_camera = std::make_unique<Camera>(Camera());
        const std::unordered_map<int, change_camera_t> m_keyMap = {
                {GLFW_KEY_W, &scene::Camera::moveForward},
                {GLFW_KEY_S, &scene::Camera::moveBackward},
                {GLFW_KEY_R, &scene::Camera::moveUp},
                {GLFW_KEY_F, &scene::Camera::moveDown},
                {GLFW_KEY_A, &scene::Camera::moveLeft},
                {GLFW_KEY_D, &scene::Camera::moveRight},
                {GLFW_KEY_Q, &scene::Camera::rotateLeft},
                {GLFW_KEY_E, &scene::Camera::rotateRight}
        };

    };
}

#endif /* !ECHESS_HPP */
