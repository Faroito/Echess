//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef DEPTH_IMAGE_HPP
# define DEPTH_IMAGE_HPP

#include "buffer-manip.hpp"
#include "devices.hpp"
#include "libraries.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    // TODO: move to framebuffer ?

    /**
     * A depth attachment is based on an image.
     */
    class DepthImage {
    public:
        DepthImage() = default;

        void setUp(Devices &devices, VkExtent2D &extent);
        void cleanUp(VkDevice &device);

        VkImageView &get();

    private:
        VkImage m_depthImage;
        VkDeviceMemory m_depthImageMemory;
        VkImageView m_depthImageView;
    };

}

#endif /* !DEPTH_IMAGE_HPP */
