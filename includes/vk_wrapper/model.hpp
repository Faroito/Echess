//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef MODEL_HPP
# define MODEL_HPP

#include <vector>
#include <memory>
#include <numeric>

#include "camera.hpp"
#include "framebuffers.hpp"
#include "graphics-pipeline.hpp"
#include "descriptor-sets.hpp"
#include "devices.hpp"
#include "mesh.hpp"
#include "libraries.hpp"
#include "texture.hpp"
#include "uniform-buffers.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     */
    class Model {
    public:
        explicit Model(ModelType type, ModelColor color);
        virtual ~Model() = default;

        void setUp(Devices &devices, GraphicsPipeline &pipeline, Framebuffers &framebuffers,
                   VkCommandPool &pool, MeshMap_t &meshes, size_t size);
        void cleanUp(VkDevice &device);

        void setPosition(glm::vec3 position);
        void setOrientation(glm::vec3 orientation);
        void setCamera(scene::Camera_ptr_t &camera, float ratio);

        virtual void update(std::vector<std::unique_ptr<Model>> &models);
        virtual void updateUniformBuffer(VkDevice &device, uint32_t currentImage);

        size_t getId() const;
        glm::vec3 getPosition() const;
        glm::vec3 getVelocity() const;
        ModelType getModelType() const;
        VkDescriptorSet &getDescriptorSet(size_t i);

    protected:
        glm::vec3 m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_offset = glm::vec3(0.0f, 0.0f, 0.0f);

    private:
        const size_t m_id;
        static size_t m_idGen;
        const ModelType m_type;
        const ModelColor m_color;

        UniformBufferObject m_ubo = {};
        UniformBuffers m_uniforms;
        DescriptorSets m_descriptorSets;
    };

    typedef std::vector<std::unique_ptr<Model>> Models_t;
}


#endif /* !MODEL_HPP */
