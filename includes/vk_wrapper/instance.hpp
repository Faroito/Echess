//
// Created by Timothée Couble on 25/09/2020.
//

#ifndef INSTANCE_HPP
# define INSTANCE_HPP

#include <vector>
#include <cstring>

#include "libraries.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * The instance is the connection between the Application and
     * the Vulkan library and creating it involves specifying some
     * details about your Application to the driver.
     *
     * It also create validation layers for debug issues.
     */
    class Instance {
    public:
        Instance() = default;

        void setUp(const std::string &name);
        void cleanUp();

        VkInstance &get();

    private:
        static bool checkValidationLayerSupport();
        static std::vector<const char *> getRequiredExtensions();

        void setupDebugMessenger();
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        VkResult CreateDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                              const VkAllocationCallbacks *pAllocator);
        void DestroyDebugUtilsMessengerEXT(const VkAllocationCallbacks *pAllocator);

        static VKAPI_ATTR VkBool32
        VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData);

    private:
        VkInstance m_instance = nullptr;
        VkDebugUtilsMessengerEXT m_debugMessenger = nullptr;

    };

}

#endif /* !INSTANCE_HPP */
