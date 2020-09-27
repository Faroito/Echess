//
// Created by Timothée Couble on 26/09/2020.
//

#include "descriptor-sets.hpp"

using namespace vk_wrapper;

void DescriptorSets::setUp(VkDevice &device, VkDescriptorSetLayout &layout, Texture &texture,
                           UniformBuffers &uniforms, size_t size) {
    createDescriptorPool(device, size);
    createDescriptorSets(device, layout, texture, uniforms, size);
}

void DescriptorSets::createDescriptorPool(VkDevice &device, size_t size) {
    std::array<VkDescriptorPoolSize, 2> poolSizes = {};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(size);
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(size);

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(size);

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS)
        throw std::runtime_error("failed to create descriptor pool!");
}

void DescriptorSets::createDescriptorSets(VkDevice &device, VkDescriptorSetLayout &layout, vk_wrapper::Texture &texture,
                                          vk_wrapper::UniformBuffers &uniforms, size_t size) {
    std::vector<VkDescriptorSetLayout> layouts(size, layout);
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = m_descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(size);
    allocInfo.pSetLayouts = layouts.data();

    m_descriptorSets.resize(size);
    if (vkAllocateDescriptorSets(device, &allocInfo, m_descriptorSets.data()) != VK_SUCCESS)
        throw std::runtime_error("failed to allocate descriptor sets!");

    for (size_t i = 0; i < size; i++) {
        VkDescriptorBufferInfo bufferInfo = {};
        bufferInfo.buffer = uniforms[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkDescriptorImageInfo imageInfo = {};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = texture.getImageView();
        imageInfo.sampler = texture.getSampler();

        std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = m_descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = m_descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(),
                               0, nullptr);
    }
}

void DescriptorSets::cleanUp(VkDevice &device) {
    vkDestroyDescriptorPool(device, m_descriptorPool, nullptr);
}

VkDescriptorSet &DescriptorSets::operator[](size_t i) {
    return m_descriptorSets[i];
}


