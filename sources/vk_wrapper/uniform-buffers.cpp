//
// Created by Timothée Couble on 26/09/2020.
//

#include "uniform-buffers.hpp"

using namespace vk_wrapper;

void UniformBuffers::setUp(Devices &devices, size_t size) {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    m_uniformBuffers.resize(size);
    m_uniformBuffersMemory.resize(size);

    for (size_t i = 0; i < size; i++)
        BufferManip::createBuffer(devices, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                  m_uniformBuffers[i], m_uniformBuffersMemory[i]);
}

void UniformBuffers::cleanUp(VkDevice &device) {
    for (size_t i = 0; i < m_uniformBuffers.size(); i++) {
        vkDestroyBuffer(device, m_uniformBuffers[i], nullptr);
        vkFreeMemory(device, m_uniformBuffersMemory[i], nullptr);
    }
}

VkBuffer &UniformBuffers::operator[](size_t i) {
    return m_uniformBuffers[i];
}

VkDeviceMemory &UniformBuffers::getMemory(size_t i) {
    return m_uniformBuffersMemory[i];
}
