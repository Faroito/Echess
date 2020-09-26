//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef FRAMEBUFFERS_HPP
# define FRAMEBUFFERS_HPP

#include <vector>
#include <array>

#include "libraries.hpp"
#include "swap-chain.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * Framebuffer for all of the images in the swap chain
     * and use the one that corresponds to the retrieved image
     * at drawing time.
     */
    class Framebuffers {
    public:
        Framebuffers() = default;

        void setUp(VkDevice &device, SwapChain &swapChain, VkRenderPass &renderPass, VkImageView &depthImageView);
        void cleanUp(VkDevice &device);

        VkFramebuffer &operator[](size_t i);
        size_t size() const;

    private:
        std::vector<VkFramebuffer> m_swapChainFramebuffers;

    };

}

#endif /* !FRAMEBUFFERS_HPP */
