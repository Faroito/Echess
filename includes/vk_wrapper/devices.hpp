//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef DEVICE_HPP
# define DEVICE_HPP

#include "libraries.hpp"
#include "surface.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * Pick a physical device that select a graphics card in
     * the system that supports the features we need.
     * And check that queues families are supported.
     *
     * Create logical devices which interface with physical device.
     * Graphics & Present queues.
     */
    class Devices {
    public:
        Devices() = default;

        void setUp(VkInstance &instance, GLFWwindow *window);
        void cleanUp(VkInstance &instance);

        VkDevice &get();
        VkPhysicalDevice &getPhysical();
        Surface &getSurface();
        VkQueue &getGraphicsQueue();
        VkQueue &getPresentQueue();

    private:
        void pickPhysicalDevice(VkInstance &instance);
        void createLogicalDevice();

    private:
        VkDevice m_logicalDevice = nullptr;
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

        Surface m_surface = Surface();

        VkQueue m_graphicsQueue = nullptr;
        VkQueue m_presentQueue = nullptr;
    };

}

#endif /* !DEVICE_HPP */
