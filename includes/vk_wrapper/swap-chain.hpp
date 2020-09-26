//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef SWAP_CHAIN_HPP
# define SWAP_CHAIN_HPP

#include <vector>

#include "buffer-manip.hpp"
#include "devices.hpp"
#include "libraries.hpp"
#include "surface.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * The swap chain is essentially a queue of images
     * that are waiting to be presented to the screen.
     *
     * It act as a Framebuffer, it's synchronize the presentation
     * of images with the refresh rate of the screen.
     *
     * Handle also ImagesView which describes how to access
     * the image (VkImage) and which part of the image to access.
     */
    class SwapChain {
    public:
        SwapChain() = default;

        void setUp(GLFWwindow *window, Devices &devices);
        void cleanUp(VkDevice &device);

        VkSwapchainKHR &get();
        VkFormat &getImageFormat();
        VkImageView &getImageView(size_t i);
        VkExtent2D &getExtent();
        size_t size();
        float ratio();


    private:
        void createSwapChain(GLFWwindow *window, Devices &devices);
        void createImageViews(VkDevice &device);

        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        static VkExtent2D chooseSwapExtent(GLFWwindow *window, const VkSurfaceCapabilitiesKHR &capabilities);

    private:
        VkSwapchainKHR m_swapChain = nullptr;
        VkFormat m_format = {}; // Color depth
        std::vector<VkImage> m_images; // Images to be presented to the swap chain
        std::vector<VkImageView> m_imageViews; // Images views
        VkExtent2D m_extent = {}; // Resolution of images

    };
}

#endif /* !SWAP_CHAIN_HPP */
