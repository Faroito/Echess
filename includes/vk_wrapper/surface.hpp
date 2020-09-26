//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef SURFACE_HPP
# define SURFACE_HPP

#include <set>

#include "libraries.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * Exposes a VkSurfaceKHR object that represents an abstract type
     * of surface to present rendered images to. The surface will be
     * backed by the window that is already opened with GLFW.
     */
    class Surface {
    public:
        Surface() = default;

        void setUp(VkInstance &instance, GLFWwindow *window);
        void cleanUp(VkInstance &instance);

        VkSurfaceKHR &get();

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);

    private:
        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    private:
        VkSurfaceKHR m_surface;

    };

}

#endif /* !SURFACE_HPP */
