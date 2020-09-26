//
// Created by Timothée Couble on 26/09/2020.
//

#include <tiny_obj_loader.h>

#include "mesh.hpp"

using namespace vk_wrapper;

Mesh::Mesh(const ModelType type) : m_type(type) {}

void Mesh::setUp(vk_wrapper::Devices &devices, VkCommandPool &pool) {
    loadModel();
    createVertexBuffer(devices, pool);
    createIndexBuffer(devices, pool);
}


void Mesh::loadModel() {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    std::string path = PATH + m_modelFile.at(m_type);

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str()))
        throw std::runtime_error(err);

    std::unordered_map<Vertex, uint32_t> uniqueVertices = {};
    for (const auto &shape : shapes) {
        for (const auto &index : shape.mesh.indices) {
            Vertex vertex = {};
            vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };
            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };
            vertex.color = {1.0f, 1.0f, 1.0f};

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(m_vertices.size());
                m_vertices.push_back(vertex);
            }
            m_indices.push_back(uniqueVertices[vertex]);
        }
    }

}

void Mesh::createVertexBuffer(vk_wrapper::Devices &devices, VkCommandPool &pool) {
    VkDeviceSize bufferSize = sizeof(m_vertices[0]) * m_vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    BufferManip::createBuffer(devices, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                              VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                              stagingBuffer, stagingBufferMemory);

    void *data;
    vkMapMemory(devices.get(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, m_vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(devices.get(), stagingBufferMemory);

    BufferManip::createBuffer(devices, bufferSize,
                              VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                              VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_vertexBuffer, m_vertexBufferMemory);

    BufferManip::copyBuffer(devices, pool, stagingBuffer, m_vertexBuffer, bufferSize);

    vkDestroyBuffer(devices.get(), stagingBuffer, nullptr);
    vkFreeMemory(devices.get(), stagingBufferMemory, nullptr);
}

void Mesh::createIndexBuffer(vk_wrapper::Devices &devices, VkCommandPool &pool) {
    VkDeviceSize bufferSize = sizeof(m_indices[0]) * m_indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    BufferManip::createBuffer(devices, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                              VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                              stagingBuffer, stagingBufferMemory);

    void *data;
    vkMapMemory(devices.get(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, m_indices.data(), (size_t) bufferSize);
    vkUnmapMemory(devices.get(), stagingBufferMemory);

    BufferManip::createBuffer(devices, bufferSize,
                              VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                              VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_indexBuffer, m_indexBufferMemory);

    BufferManip::copyBuffer(devices, pool, stagingBuffer, m_indexBuffer, bufferSize);

    vkDestroyBuffer(devices.get(), stagingBuffer, nullptr);
    vkFreeMemory(devices.get(), stagingBufferMemory, nullptr);
}

void Mesh::cleanUp(VkDevice &device) {
    vkDestroyBuffer(device, m_vertexBuffer, nullptr);
    vkFreeMemory(device, m_vertexBufferMemory, nullptr);
    vkDestroyBuffer(device, m_indexBuffer, nullptr);
    vkFreeMemory(device, m_indexBufferMemory, nullptr);
}

VkBuffer &Mesh::getVertexBuffer() {
    return m_vertexBuffer;
}

VkBuffer &Mesh::getIndexBuffer() {
    return m_indexBuffer;
}

uint32_t Mesh::getIndicesSize() const {
    return m_indices.size();
}