//
// Created by Timothée Couble on 25/09/2020.
//

#ifndef IAPPLICATION_HPP
# define IAPPLICATION_HPP

#include "libraries.hpp"

namespace vk_wrapper {

    /**
     * Interface for Application help to handle keys and other events.
     */
    class IApplication {
    public:
        virtual void onMouseMove(double x, double y) = 0;
        virtual void onMouseDown(int button, int action) = 0;
        virtual void onMouseScroll(double x, double y) = 0;
        virtual void onKeyDown(int key, int action) = 0;
    };

    struct CallbackInterface {
        static IApplication *app;

        static void OnKeyDown(GLFWwindow *window, int key, int scancode, int action, int mods) {
            app->onKeyDown(key, action);
        }
        static void OnMouseMove(GLFWwindow *window, double x, double y) {
            app->onMouseMove(x, y);
        }
        static void OnMouseDown(GLFWwindow *window, int button, int action, int mods) {
            app->onMouseDown(button, action);
        }
        static void OnMouseScroll(GLFWwindow *window, double x, double y) {
            app->onMouseScroll(x, y);
        }
    };

};


#endif /* !IAPPLICATION_HPP */
