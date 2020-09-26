//
// Created by Timothée Couble on 26/09/2020.
//

#include "model.hpp"

using namespace vk_wrapper;

size_t Model::m_idGen = 0;

Model::Model(const vk_wrapper::ModelType type, const vk_wrapper::ModelColor color)
        : m_type(type), m_color(color), m_id(m_idGen++) {}

void
Model::setUp(vk_wrapper::Devices &devices, vk_wrapper::SwapChain &swapChain,
             vk_wrapper::GraphicsPipeline &pipeline,
             vk_wrapper::Framebuffers &framebuffers, VkCommandPool &pool, TextureMap_t &textures) {
    m_uniforms.setUp(devices, swapChain.size());
    m_descriptorSets.setUp(devices.get(), swapChain, pipeline.getDescriptorSetLayout(), textures.at(m_color),
                           m_uniforms);
}

void Model::cleanUp(VkDevice &device) {
    m_descriptorSets.cleanUp(device);
    m_uniforms.cleanUp(device);
}

void Model::setPosition(glm::vec3 position) {
    _position = position;
}

void Model::setOrientation(glm::vec3 orientation) {
    _orientation = orientation;
}

void Model::setCamera(scene::Camera_ptr_t &_camera, float ratio) {
    m_ubo.view = _camera->getViewMatrix();
    m_ubo.proj = _camera->getProjectionMatrix(ratio);
}

void Model::update(std::vector<std::unique_ptr<Model>> &models) {}

void Model::updateUniformBuffer(VkDevice &device, uint32_t currentImage) {
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), _position - _offset);
    glm::mat4 rotate = glm::translate(glm::mat4(1.0f), _offset);
    rotate = glm::rotate(rotate, glm::radians(_orientation.x), glm::vec3(1.f, 0.f, 0.f));
    rotate = glm::rotate(rotate, glm::radians(_orientation.y), glm::vec3(0.f, 1.f, 0.f));
    rotate = glm::rotate(rotate, glm::radians(_orientation.z), glm::vec3(0.f, 0.f, 1.f));
    rotate = glm::translate(rotate, -_offset);
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
    return _position;
}

glm::vec3 Model::getVelocity() const {
    return _velocity;
}

ModelType Model::getModelType() const {
    return m_type;
}

VkDescriptorSet &Model::getDescriptorSet(size_t i) {
    return m_descriptorSets[i];
}

