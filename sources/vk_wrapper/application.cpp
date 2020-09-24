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
//    m_surface.setUp(m_instance.get(), m_window.get());
//    m_devices.setUp(m_instance.get(), m_surface);
//    m_swapChain.setUp(m_window.get(), m_surface, m_devices);
//    m_pipeline.setUp(m_devices, m_swapChain);
//    m_commandPool.setUp(m_devices.get(), m_surface.findQueueFamilies(m_devices.getPhysical()));
//    m_depthImage.setUp(m_devices, m_swapChain.getExtent());
//    m_framebuffers.setUp(m_devices.get(), m_swapChain, m_pipeline.getRenderPass(), m_depthImage.get());
//    m_syncObjects.setUp(m_devices.get(), m_swapChain.size());
}

void Application::initModels() {
//    const ModelType allType[] = {PAPER_PLANE};
//
//    for (const auto &type : allType) {
//        m_meshes.emplace(type, Mesh(type));
//        m_meshes.at(type).setUp(m_devices, m_commandPool.get());
//    }
//    for (const auto &color : COLORS_AVAILABLE) {
//        m_textures.emplace(color, Texture(color));
//        m_textures.at(color).setUp(m_devices, m_commandPool.get());
//    }
//
//    for (auto &model : m_models)
//        model->setUp(m_devices, m_swapChain, m_pipeline, m_framebuffers, m_commandPool.get(), m_textures);
//    m_commandBuffers.setUp(m_devices.get(), m_swapChain, m_pipeline, m_framebuffers, m_commandPool.get(), m_meshes,
//                           m_models);
}

void Application::run() {
    while (!m_window.shouldClose()) {
        glfwPollEvents();
        this->onDraw();
    }

//    vkDeviceWaitIdle(m_devices.get());
}

void Application::onDraw() {
//    if (m_syncObjects.drawFrame(m_devices, m_swapChain, m_models, m_commandBuffers, m_window.resized)) {
//        m_window.resized = false;
//        recreateSwapChain();
//    }
}

void Application::cleanup() {
    cleanupSwapChain();

//    for (auto &mesh : m_meshes)
//        mesh.second.cleanUp(m_devices.get());
//    for (auto &texture : m_textures)
//        texture.second.cleanUp(m_devices.get());
//    m_syncObjects.cleanUp(m_devices.get());
//    m_commandPool.cleanUp(m_devices.get());
//    m_devices.cleanUp();
//    m_surface.cleanUp(m_instance.get());
    m_instance.cleanUp();
    m_window.cleanUp();
}

void Application::cleanupSwapChain() {
//    m_depthImage.cleanUp(m_devices.get());
//    m_framebuffers.cleanUp(m_devices.get());
//    m_commandBuffers.cleanUp(m_devices.get(), m_commandPool.get());
//    for (auto &model : m_models)
//        model->cleanUp(m_devices.get());
//    m_pipeline.cleanUp(m_devices.get());
//    m_swapChain.cleanUp(m_devices.get());
}

void Application::recreateSwapChain() {
    m_window.resize();
//    vkDeviceWaitIdle(m_devices.get());

    cleanupSwapChain();

//    m_swapChain.setUp(m_window.get(), m_surface, m_devices);
//    m_pipeline.setUp(m_devices, m_swapChain);
//    m_depthImage.setUp(m_devices, m_swapChain.getExtent());
//    m_framebuffers.setUp(m_devices.get(), m_swapChain, m_pipeline.getRenderPass(), m_depthImage.get());
//    for (auto &model : m_models)
//        model->setUp(m_devices, m_swapChain, m_pipeline, m_framebuffers, m_commandPool.get(), m_textures);
//    m_commandBuffers.setUp(m_devices.get(), m_swapChain, m_pipeline, m_framebuffers, m_commandPool.get(), m_meshes,
//                           m_models);
}

void Application::onMouseMove(double x, double y) {}

void Application::onMouseDown(int button, int action) {}

void Application::onMouseScroll(double x, double y) {}

void Application::onKeyDown(int key, int action) {}
