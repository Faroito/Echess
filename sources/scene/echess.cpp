//
// Created by Timothée Couble on 25/09/2020.
//

#include "echess.hpp"

using namespace scene;

Echess::Echess() : vk_wrapper::Application("Echess") {
    initModels();
    std::srand(std::time(nullptr));
}

void Echess::initModels() {

//    const size_t planeNb = 30;
//    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
//
//    auto findBlock = [&position](std::unique_ptr<vk_wrapper::Model> &obj) { return obj->getPosition() == position; };
//    for (size_t i = 0; i < planeNb; i++) {
//        do {
//            position = glm::vec3(rand() % 7 - 3, (rand() % 13 - 6) * 0.5, (rand() % 5) * 1.5);
//        } while (std::find_if(std::begin(m_models), std::end(m_models), findBlock) != std::end(_models));
//        m_models.push_back(std::make_unique<PaperPlane>(PaperPlane(vk_wrapper::COLORS_AVAILABLE[i % 7])));
//        m_models.back()->setPosition(position);
//    }

    Application::initModels();
}

void Echess::onDraw() {
    checkKey();

    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

//    for (auto &model : m_models) {
//        if (time > 0.02) {
//            startTime = std::chrono::high_resolution_clock::now();
//            model->update(m_models);
//        }
//        model->setCamera(m_camera, m_swapChain.ratio());
//    }
    Application::onDraw();
}

void Echess::checkKey() {
    for (const auto &it : m_keyMap) {
        if (m_keyCode[it.first] && m_pressed)
            (m_camera.get()->*it.second)();
    }
    if (m_keyCode[GLFW_KEY_ESCAPE])
        m_window.close();
}

void Echess::onMouseMove(double x, double y) {
    // std::cout << x << " " << y << std::endl;
}

void Echess::onMouseDown(int button, int action) {
    if (action == GLFW_PRESS)
        std::cout << "Clicked on: " << button << std::endl;
}

void Echess::onMouseScroll(double x, double y) {
    m_camera->zoom(y);
}

void Echess::onKeyDown(int key, int action) {
    if (action == GLFW_PRESS) {
        m_pressed = true;
        m_keyCode[key] = true;
    }
    if (action == GLFW_RELEASE) {
        m_pressed = false;
        m_keyCode[key] = false;
    }
}