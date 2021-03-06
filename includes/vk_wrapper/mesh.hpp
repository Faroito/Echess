//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef MESH_HPP
# define MESH_HPP

#include <vector>
#include <unordered_map>

#include "buffer-manip.hpp"
#include "devices.hpp"
#include "libraries.hpp"
#include "texture.hpp"
#include "utils.hpp"
#include "vertex.hpp"

namespace vk_wrapper {

    /**
     * Load the vertices and indices from an obj model file.
     */
    class Mesh {
    public:
        explicit Mesh(ModelType type);

        void setUp(Devices &devices, VkCommandPool &pool);
        void cleanUp(VkDevice &device);

        VkBuffer &getVertexBuffer();
        VkBuffer &getIndexBuffer();
        uint32_t getIndicesSize() const;
        Texture &getTexture(ModelColor color);

    private:
        void loadModel();
        void createVertexBuffer(Devices &devices, VkCommandPool &pool);
        void createIndexBuffer(Devices &devices, VkCommandPool &pool);
        void loadTextures(Devices &devices, VkCommandPool &pool);

    private:
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;

        VkBuffer m_vertexBuffer = nullptr;
        VkDeviceMemory m_vertexBufferMemory = nullptr;
        VkBuffer m_indexBuffer = nullptr;
        VkDeviceMemory m_indexBufferMemory = nullptr;

        const ModelType m_type;
        TextureMap_t m_textures;

        const std::vector<std::string> m_modelTypeName = {"pawn"};
        const std::vector<std::string> m_modelColorName = {"white", "black"};
    };

    typedef std::unordered_map<ModelType, Mesh> MeshMap_t;
}

#endif /* !MESH_HPP */
