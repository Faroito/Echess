//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef PAWN_HPP
# define PAWN_HPP

#include <algorithm>
#include <cmath>
#include <chrono>

#include "model.hpp"
#include "utils.hpp"

namespace scene {

    class Pawn : public vk_wrapper::Model {
    public:
        explicit Pawn(vk_wrapper::ModelColor color);
        ~Pawn() override = default;

        void update(vk_wrapper::Models_t &models) override;
        void updateUniformBuffer(VkDevice &device, uint32_t currentImage) override;
    };
}

std::ostream &operator<<(std::ostream &stream, const glm::vec3 &vec);

#endif /* !PAWN_HPP */
