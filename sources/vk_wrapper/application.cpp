//
// Created by Timothée Couble on 25/09/2020.
//

#include "application.hpp"

using namespace vk_wrapper;

Application::Application(const std::string &appName) : m_appName(appName) {
    m_window.setUp(this, m_appName);
    initVulkan();
}

Application::~Application() {
    cleanup();
}

void Application::initVulkan() {
    m_instance.setUp(m_appName);
    m_devices.setUp(m_instance.get(), m_window.get());
    m_swapChain.setUp(m_window.get(), m_devices);
    m_pipeline.setUp(m_devices, m_swapChain);
    m_commandPool.setUp(m_devices);
    m_framebuffers.setUp(m_devices, m_swapChain, m_pipeline.getRenderPass());
    m_syncObjects.setUp(m_devices.get(), m_swapChain.size());
}

void Application::initModels() {
    for (const auto &type : TYPE_AVAILABLE) {
        m_meshes.emplace(type, Mesh(type));
        m_meshes.at(type).setUp(m_devices, m_commandPool.get());
    }

    for (auto &model : m_models)
        model->setUp(m_devices, m_pipeline, m_framebuffers, m_commandPool.get(),
                     m_meshes, m_swapChain.size());
    m_commandBuffers.setUp(m_devices.get(), m_swapChain, m_pipeline, m_framebuffers,
                           m_commandPool.get(), m_meshes, m_models);
}

void Application::run() {
    while (!m_window.shouldClose()) {
        glfwPollEvents();
        this->onDraw();
    }

    vkDeviceWaitIdle(m_devices.get());
}

void Application::onDraw() {
    if (m_syncObjects.drawFrame(m_devices, m_swapChain, m_models,
                                m_commandBuffers, m_window.resized)) {
        m_window.resized = false;
        recreateSwapChain();
    }
}

void Application::cleanup() {
    cleanupSwapChain();

    for (auto &mesh : m_meshes)
        mesh.second.cleanUp(m_devices.get());
    m_syncObjects.cleanUp(m_devices.get());
    m_commandPool.cleanUp(m_devices.get());
    m_devices.cleanUp(m_instance.get());
    m_instance.cleanUp();
    m_window.cleanUp();
}

void Application::cleanupSwapChain() {
    m_framebuffers.cleanUp(m_devices.get());
    m_commandBuffers.cleanUp(m_devices.get(), m_commandPool.get());
    for (auto &model : m_models)
        model->cleanUp(m_devices.get());
    m_pipeline.cleanUp(m_devices.get());
    m_swapChain.cleanUp(m_devices.get());
}

void Application::recreateSwapChain() {
    m_window.resize();
    vkDeviceWaitIdle(m_devices.get());

    cleanupSwapChain();

    m_swapChain.setUp(m_window.get(), m_devices);
    m_pipeline.setUp(m_devices, m_swapChain);
    m_framebuffers.setUp(m_devices, m_swapChain, m_pipeline.getRenderPass());
    for (auto &model : m_models)
        model->setUp(m_devices, m_pipeline, m_framebuffers, m_commandPool.get(),
                     m_meshes, m_swapChain.size());
    m_commandBuffers.setUp(m_devices.get(), m_swapChain, m_pipeline, m_framebuffers,
                           m_commandPool.get(), m_meshes, m_models);
}

void Application::onMouseMove(double x, double y) {}

void Application::onMouseDown(int button, int action) {}

void Application::onMouseScroll(double x, double y) {}

void Application::onKeyDown(int key, int action) {}
