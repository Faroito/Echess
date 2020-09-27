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

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    /**
     * Uniform buffer objects (UBO).
     *
     * Contains all transformations done on a model (view, proj & model)
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
