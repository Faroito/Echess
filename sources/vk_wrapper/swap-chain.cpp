//
// Created by Timothée Couble on 26/09/2020.
//

#include "swap-chain.hpp"

using namespace vk_wrapper;

void SwapChain::setUp(GLFWwindow *window, Devices &devices) {
    createSwapChain(window, devices);
    createImageViews(devices.get());
}

void SwapChain::createSwapChain(GLFWwindow *window, Devices &devices) {
    Surface &surface = devices.getSurface();
    SwapChainSupportDetails supportDetails = surface.querySwapChainSupport(devices.getPhysical());

    VkSurfaceFormatKHR surfaceFormat = SwapChain::chooseSwapSurfaceFormat(supportDetails.formats);
    VkPresentModeKHR presentMode = SwapChain::chooseSwapPresentMode(supportDetails.presentModes);
    VkExtent2D extent = SwapChain::chooseSwapExtent(window, supportDetails.capabilities);

    uint32_t imageCount = supportDetails.capabilities.minImageCount + 1;
    if (supportDetails.capabilities.maxImageCount > 0 && imageCount > supportDetails.capabilities.maxImageCount) {
        imageCount = supportDetails.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface.get();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = devices.getQueueFamilies();
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    createInfo.preTransform = supportDetails.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(devices.get(), &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
        throw std::runtime_error("failed to create swap chain!");

    vkGetSwapchainImagesKHR(devices.get(), m_swapChain, &imageCount, nullptr);
    m_images.resize(imageCount);
    vkGetSwapchainImagesKHR(devices.get(), m_swapChain, &imageCount, m_images.data());

    m_extent = extent;
    m_format = surfaceFormat.format;
}

void SwapChain::createImageViews(VkDevice &device) {
    m_imageViews.resize(m_images.size());

    for (uint32_t i = 0; i < m_images.size(); i++)
        m_imageViews[i] = BufferManip::createImageView(device, m_images[i],
                                                       m_format, VK_IMAGE_ASPECT_COLOR_BIT);

}

void SwapChain::cleanUp(VkDevice &device) {
    for (auto &imageView : m_imageViews)
        vkDestroyImageView(device, imageView, nullptr);
    vkDestroySwapchainKHR(device, m_swapChain, nullptr);
}

VkSwapchainKHR &SwapChain::get() {
    return m_swapChain;
}

VkFormat &SwapChain::getImageFormat() {
    return m_format;
}

VkImageView &SwapChain::getImageView(size_t i) {
    return m_imageViews[i];
}

VkExtent2D &SwapChain::getExtent() {
    return m_extent;
}

size_t SwapChain::size() {
    return m_images.size();
}

float SwapChain::ratio() {
    return m_extent.width / (float) m_extent.height;
}

/**
 * Return the color channels and types.
 */
VkSurfaceFormatKHR
SwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) {
    for (const auto &availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return availableFormat;
    }

    return availableFormats[0];
}

/**
 * Return the conditions mode for showing images to the screen.
 */
VkPresentModeKHR
SwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes) {
    for (const auto &availablePresentMode : availablePresentModes)
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            return availablePresentMode;

    return VK_PRESENT_MODE_FIFO_KHR;
}

/**
 * Return the resolution of the swap chain images.
 */
VkExtent2D SwapChain::chooseSwapExtent(GLFWwindow *window, const VkSurfaceCapabilitiesKHR &capabilities) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
        };

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}
