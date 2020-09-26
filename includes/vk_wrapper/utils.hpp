//
// Created by Timothée Couble on 25/09/2020.
//

#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <vector>
#include <optional>
#include <fstream>
#include <cstdint>
#include <cstdlib>

#include "libraries.hpp"

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace vk_wrapper {
    const int WIDTH = 1024;
    const int HEIGHT = 768;
    const int MAX_FRAMES_IN_FLIGHT = 2;

    const std::string PATH = "../Resources/";
    const VkClearColorValue BACKGROUND_COLOR = {0.07f, 0.17f, 0.24f, 1.0f};

    const std::vector<const char *> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };
    const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    enum ModelType {
        PAPER_PLANE
    };

    enum ModelColor {
        BLUE,
        CYAN,
        ORANGE,
        RED,
        GREEN,
        PURPLE,
        YELLOW
    };

    const ModelColor COLORS_AVAILABLE[] = {BLUE, CYAN, ORANGE, RED, GREEN, PURPLE, YELLOW};

    std::vector<char> readFile(const std::string &filename);
    VkFormat findDepthFormat(VkPhysicalDevice &device);
    uint32_t findMemoryType(VkPhysicalDevice &device, uint32_t typeFilter, VkMemoryPropertyFlags properties);
}

#endif /* !UTILS_HPP */
