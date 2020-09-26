//
// Created by Timothée Couble on 26/09/2020.
//

#include "framebuffers.hpp"

using namespace vk_wrapper;

void Framebuffers::setUp(VkDevice &device, vk_wrapper::SwapChain &swapChain,
                         VkRenderPass &renderPass, VkImageView &depthImageView) {
    m_swapChainFramebuffers.resize(swapChain.size());

    for (size_t i = 0; i < swapChain.size(); i++) {
        std::array<VkImageView, 2> attachments = {
                swapChain.getImageView(i),
                depthImageView
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swapChain.getExtent().width;
        framebufferInfo.height = swapChain.getExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("failed to create framebuffer!");
    }
}

void Framebuffers::cleanUp(VkDevice &device) {
    for (auto &framebuffer : m_swapChainFramebuffers)
        vkDestroyFramebuffer(device, framebuffer, nullptr);
}

VkFramebuffer &Framebuffers::operator[](size_t i) {
    return m_swapChainFramebuffers[i];
}

size_t Framebuffers::size() const {
    return m_swapChainFramebuffers.size();
}
