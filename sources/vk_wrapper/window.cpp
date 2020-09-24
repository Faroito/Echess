//
// Created by Timothée Couble on 25/09/2020.
//

#include "window.hpp"

using namespace vk_wrapper;

IApplication *CallbackInterface::app;

void Window::setUp(IApplication *app, const std::string &appName) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(WIDTH, HEIGHT, appName.c_str(), nullptr, nullptr);

    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("failed to create glfw window!");
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);

    vk_wrapper::CallbackInterface::app = app;

    glfwSetKeyCallback(m_window, vk_wrapper::CallbackInterface::OnKeyDown);
    glfwSetCursorPosCallback(m_window, vk_wrapper::CallbackInterface::OnMouseMove);
    glfwSetMouseButtonCallback(m_window, vk_wrapper::CallbackInterface::OnMouseDown);
    glfwSetScrollCallback(m_window, vk_wrapper::CallbackInterface::OnMouseScroll);
}

void Window::cleanUp() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

GLFWwindow *Window::get() {
    return m_window;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_window);
}

void Window::resize() {
    int width = 0, height = 0;
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(m_window, &width, &height);
        if (width == 0 || height == 0)
            glfwWaitEvents();
    }
}

void Window::close() {
    glfwSetWindowShouldClose(m_window, true);
}

void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
    auto app = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    app->resized = true;
}

