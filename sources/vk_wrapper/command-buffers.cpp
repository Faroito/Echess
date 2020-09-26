//
// Created by Timothée Couble on 09/12/2019.
//

#include "command-buffers.hpp"

using namespace vk_wrapper;

void CommandBuffers::setUp(VkDevice &device, SwapChain &swapChain, GraphicsPipeline &pipeline,
                           Framebuffers &framebuffers, VkCommandPool &pool,
                           MeshMap_t &meshes, Models_t &models) {
    m_commandBuffers.resize(framebuffers.size());

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = pool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) m_commandBuffers.size();

    if (vkAllocateCommandBuffers(device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS)
        throw std::runtime_error("failed to allocate command buffers!");

    for (size_t i = 0; i < m_commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = pipeline.getRenderPass();
        renderPassInfo.framebuffer = framebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain.getExtent();

        std::array<VkClearValue, 2> clearValues = {};
        clearValues[0].color = BACKGROUND_COLOR;
        clearValues[1].depthStencil = {1.0f, 0};

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.get());

        // TODO: use https://stackoverflow.com/questions/50956414/what-is-a-push-constant-in-vulkan instead
        for (auto &mesh : meshes) {
            VkBuffer vertexBuffers[] = {mesh.second.getVertexBuffer()};
            VkDeviceSize offsets[] = {0};

            vkCmdBindVertexBuffers(m_commandBuffers[i], 0, 1, vertexBuffers, offsets);
            vkCmdBindIndexBuffer(m_commandBuffers[i], mesh.second.getIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);

            for (auto &model : models) {
                if (model->getModelType() == mesh.first) {
                    vkCmdBindDescriptorSets(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,
                                            pipeline.getLayout(), 0, 1, &model->getDescriptorSet(i), 0, nullptr);
                    vkCmdDrawIndexed(m_commandBuffers[i], mesh.second.getIndicesSize(), 1, 0, 0, 0);
                }
            }
        }

        vkCmdEndRenderPass(m_commandBuffers[i]);

        if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("failed to record command buffer!");
    }
}

void CommandBuffers::cleanUp(VkDevice &device, VkCommandPool &pool) {
    vkFreeCommandBuffers(device, pool,
                         static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
}

VkCommandBuffer &CommandBuffers::operator[](size_t i) {
    return m_commandBuffers[i];
}

size_t CommandBuffers::size() const {
    return m_commandBuffers.size();
}
