//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef DESCRIPTOR_SETS_HPP
# define DESCRIPTOR_SETS_HPP

#include <vector>

#include "devices.hpp"
#include "libraries.hpp"
#include "swap-chain.hpp"
#include "texture.hpp"
#include "uniform-buffers.hpp"

namespace vk_wrapper {

    /**
     *
     */
    class DescriptorSets {
    public:
        DescriptorSets() = default;

        void setUp(VkDevice &device, SwapChain &swapChain, VkDescriptorSetLayout &layout,
                   Texture &texture, UniformBuffers &uniforms);
        void cleanUp(VkDevice &device);

        VkDescriptorSet &operator[](size_t i);

    private:
        void createDescriptorPool(VkDevice &device, size_t size);
        void createDescriptorSets(VkDevice &device, size_t size, VkDescriptorSetLayout &layout,
                                  Texture &texture, UniformBuffers &uniforms);

    private:
        VkDescriptorPool m_descriptorPool = nullptr;
        std::vector<VkDescriptorSet> m_descriptorSets;
    };

}

#endif /* !DESCRIPTOR_SETS_HPP */
