//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef UNIFORM_BUFFERS_HPP
# define UNIFORM_BUFFERS_HPP

#include <vector>
#include <array>

#include "buffer-manip.hpp"
#include "devices.hpp"
#include "libraries.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * Uniform buffer objects (UBO).
     */
    class UniformBuffers {
    public:
        UniformBuffers() = default;

        void setUp(Devices &devices, size_t size);
        void cleanUp(VkDevice &device);

        VkBuffer &operator[](size_t i);
        VkDeviceMemory &getMemory(size_t i);

    private:
        std::vector<VkBuffer> m_uniformBuffers;
        std::vector<VkDeviceMemory> m_uniformBuffersMemory;

    };

}

#endif /* !UNIFORM_BUFFERS_HPP */
