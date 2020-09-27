//
// Created by Timothée Couble on 26/09/2020.
//

#include "model.hpp"

using namespace vk_wrapper;

size_t Model::m_idGen = 0;

Model::Model(const ModelType type, const ModelColor color)
        : m_type(type), m_color(color), m_id(m_idGen++) {}

void Model::setUp(Devices &devices, GraphicsPipeline &pipeline, Framebuffers &framebuffers,
                  VkCommandPool &pool, TextureMap_t &textures, size_t size) {
    m_uniforms.setUp(devices, size);
    m_descriptorSets.setUp(devices.get(), pipeline.getDescriptorSetLayout(),
                           textures.at(m_color), m_uniforms, size);
}

void Model::cleanUp(VkDevice &device) {
    m_descriptorSets.cleanUp(device);
    m_uniforms.cleanUp(device);
}

void Model::setPosition(glm::vec3 position) {
    m_position = position;
}

void Model::setOrientation(glm::vec3 orientation) {
    m_orientation = orientation;
}

void Model::setCamera(scene::Camera_ptr_t &camera, float ratio) {
    m_ubo.view = camera->getViewMatrix();
    m_ubo.proj = camera->getProjectionMatrix(ratio);
}

void Model::update(std::vector<std::unique_ptr<Model>> &models) {}

void Model::updateUniformBuffer(VkDevice &device, uint32_t currentImage) {
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_position - m_offset);
    glm::mat4 rotate = glm::translate(glm::mat4(1.0f), m_offset);
    rotate = glm::rotate(rotate, glm::radians(m_orientation.x), glm::vec3(1.f, 0.f, 0.f));
    rotate = glm::rotate(rotate, glm::radians(m_orientation.y), glm::vec3(0.f, 1.f, 0.f));
    rotate = glm::rotate(rotate, glm::radians(m_orientation.z), glm::vec3(0.f, 0.f, 1.f));
    rotate = glm::translate(rotate, -m_offset);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    m_ubo.model = translate * rotate * scale;

    void *data;
    vkMapMemory(device, m_uniforms.getMemory(currentImage), 0, sizeof(m_ubo), 0, &data);
    memcpy(data, &m_ubo, sizeof(m_ubo));
    vkUnmapMemory(device, m_uniforms.getMemory(currentImage));
}

size_t Model::getId() const {
    return m_id;
}

glm::vec3 Model::getPosition() const {
    return m_position;
}

glm::vec3 Model::getVelocity() const {
    return m_velocity;
}

ModelType Model::getModelType() const {
    return m_type;
}

VkDescriptorSet &Model::getDescriptorSet(size_t i) {
    return m_descriptorSets[i];
}

