//
// Created by Timothée Couble on 26/09/2020.
//

#include "framebuffers.hpp"

using namespace vk_wrapper;

void Framebuffers::setUp(Devices &devices, SwapChain &swapChain, VkRenderPass &renderPass) {
    m_depthImage.setUp(devices, swapChain.getExtent());
    m_swapChainFramebuffers.resize(swapChain.size());

    for (size_t i = 0; i < swapChain.size(); i++) {
        std::array<VkImageView, 2> attachments = {
                swapChain.getImageView(i),
                m_depthImage.get()
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swapChain.getExtent().width;
        framebufferInfo.height = swapChain.getExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(devices.get(), &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("failed to create framebuffer!");
    }
}

void Framebuffers::cleanUp(VkDevice &device) {
    m_depthImage.cleanUp(device);
    for (auto &framebuffer : m_swapChainFramebuffers)
        vkDestroyFramebuffer(device, framebuffer, nullptr);
}

VkFramebuffer &Framebuffers::operator[](size_t i) {
    return m_swapChainFramebuffers[i];
}

size_t Framebuffers::size() const {
    return m_swapChainFramebuffers.size();
}
