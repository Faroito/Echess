//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef COMMAND_BUFFERS_HPP
# define COMMAND_BUFFERS_HPP

#include <vector>
#include <array>

#include "framebuffers.hpp"
#include "graphics-pipeline.hpp"
#include "libraries.hpp"
#include "swap-chain.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "uniform-buffers.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * Record all of the operations to perform in command buffer objects.
     * Vulkan execute the commands in the main loop.
     */
    class CommandBuffers {
    public:
        CommandBuffers() = default;

        void setUp(VkDevice &device, SwapChain &swapChain, GraphicsPipeline &pipeline, Framebuffers &framebuffers,
                   VkCommandPool &pool, MeshMap_t &meshes, Models_t &models);
        void cleanUp(VkDevice &device, VkCommandPool &pool);

        VkCommandBuffer &operator[](size_t i);
        size_t size() const;

    private:
        std::vector<VkCommandBuffer> m_commandBuffers;
    };

}

#endif /* !COMMAND_BUFFERS_HPP */
