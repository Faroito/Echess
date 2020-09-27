//
// Created by Timothée Couble on 26/09/2020.
//

#include "command-pool.hpp"

using namespace vk_wrapper;

void CommandPool::setUp(Devices &devices) {
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = devices.getQueueFamilies().graphicsFamily.value();
    poolInfo.flags = 0;

    if (vkCreateCommandPool(devices.get(), &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
        throw std::runtime_error("failed to create command pool!");
}

void CommandPool::cleanUp(VkDevice &device) {
    vkDestroyCommandPool(device, m_commandPool, nullptr);

}

VkCommandPool &CommandPool::get() {
    return m_commandPool;
}
