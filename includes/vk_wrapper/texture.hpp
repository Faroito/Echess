//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <unordered_map>
#include <string>

#include "buffer-manip.hpp"
#include "devices.hpp"
#include "libraries.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    class Texture {
    public:
        explicit Texture(ModelColor color);

        void setUp(Devices &devices, VkCommandPool &pool);
        void cleanUp(VkDevice &device);

        VkImageView &getImageView();
        VkSampler &getSampler();

    private:
        void createTextureImage(Devices &devices, VkCommandPool &pool, const std::string &textureName);
        void createTextureImageView(VkDevice &device);
        void createTextureSampler(VkDevice &device);

    private:
        VkImage m_textureImage = nullptr;
        VkDeviceMemory m_textureImageMemory = nullptr;
        VkImageView m_textureImageView = nullptr;
        VkSampler m_textureSampler = nullptr;

        const ModelColor m_color;
        const std::unordered_map<ModelColor, std::string> m_textureFile = {
                {ModelColor::BLUE,   "pp_blue_texture.png"},
                {ModelColor::ORANGE, "pp_orange_texture.png"},
                {ModelColor::PURPLE, "pp_purple_texture.png"},
                {ModelColor::CYAN,   "pp_cyan_texture.png"},
                {ModelColor::RED,    "pp_red_texture.png"},
                {ModelColor::GREEN,  "pp_green_texture.png"},
                {ModelColor::YELLOW, "pp_yellow_texture.png"}
        };
    };

    typedef std::unordered_map<ModelColor, Texture> TextureMap_t;
}

#endif /* !TEXTURE_HPP */