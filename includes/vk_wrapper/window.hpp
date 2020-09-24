//
// Created by Timothée Couble on 25/09/2020.
//

#ifndef WINDOW_HPP
# define WINDOW_HPP

#include "i-application.hpp"
#include "libraries.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * GLFWWindow class abstraction.
     */
    class Window {
    public:
        Window() = default;

        void setUp(IApplication *app, const std::string &appName);
        void cleanUp();

        GLFWwindow *get();
        bool shouldClose();

        void resize();
        void close();

    private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

    public:
        bool resized = false;

    private:
        GLFWwindow *m_window = nullptr;
    };

}

#endif /* !WINDOW_HPP */
