//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef GRAPHICS_PIPELINE_HPP
# define GRAPHICS_PIPELINE_HPP

#include <vector>
#include <array>

#include "devices.hpp"
#include "libraries.hpp"
#include "swap-chain.hpp"
#include "utils.hpp"
#include "vertex.hpp"

namespace vk_wrapper {

    /**
     * Handle graphic pipeline and render pass.
     *
     * The graphics pipeline is the sequence of operations
     * that take the vertices and textures of your meshes
     * all the way to the pixels in the render targets.
     */
    class GraphicsPipeline {
    public:
        GraphicsPipeline() = default;

        void setUp(Devices &device, SwapChain &swapChain);
        void cleanUp(VkDevice &device);

        VkPipeline &get();
        VkRenderPass &getRenderPass();
        VkPipelineLayout &getLayout();
        VkDescriptorSetLayout &getDescriptorSetLayout();

    private:
        void createRenderPass(Devices &device, SwapChain &swapChain);
        void createDescriptorSetLayout(VkDevice &device);
        void createGraphicsPipeline(VkDevice &device, SwapChain &swapChain);

        static VkShaderModule createShaderModule(VkDevice &device, const std::vector<char> &code);

    private:
        VkRenderPass m_renderPass = nullptr;
        VkPipeline m_graphicsPipeline = nullptr;
        VkPipelineLayout m_pipelineLayout = nullptr;
        VkDescriptorSetLayout m_descriptorSetLayout = nullptr;

    };

}

#endif /* !GRAPHICS_PIPELINE_HPP */
