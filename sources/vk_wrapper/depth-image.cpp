//
// Created by Timothée Couble on 26/09/2020.
//

#include "depth-image.hpp"

using namespace vk_wrapper;

void DepthImage::setUp(Devices &devices, VkExtent2D &extent) {
    VkFormat depthFormat = findDepthFormat(devices.getPhysical());

    BufferManip::createImage(devices, extent.width, extent.height, depthFormat,
                             VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depthImage, m_depthImageMemory);
    m_depthImageView = BufferManip::createImageView(devices.get(), m_depthImage, depthFormat,
                                                    VK_IMAGE_ASPECT_DEPTH_BIT);
}

void DepthImage::cleanUp(VkDevice &device) {
    vkDestroyImageView(device, m_depthImageView, nullptr);
    vkDestroyImage(device, m_depthImage, nullptr);
    vkFreeMemory(device, m_depthImageMemory, nullptr);
}

VkImageView &DepthImage::get() {
    return m_depthImageView;
}
