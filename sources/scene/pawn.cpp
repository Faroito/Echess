//
// Created by Timothée Couble on 04/02/2020.
//

#include "pawn.hpp"

using namespace scene;

Pawn::Pawn(vk_wrapper::ModelColor color) : vk_wrapper::Model(vk_wrapper::PAWN, color) {
    m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Pawn::update(vk_wrapper::Models_t &models) {

}

void Pawn::updateUniformBuffer(VkDevice &device, uint32_t currentImage) {
    glm::vec3 left_vector = glm::normalize(m_velocity);

    double pitch = 0;
    if (left_vector.y < 0)
        pitch = glm::asin(left_vector.y) * (180 / M_PI);
    else
        pitch = -glm::asin(left_vector.y) * (180 / M_PI);
    double yaw = glm::atan(left_vector.x, left_vector.z) * (180 / M_PI);

//    m_orientation = glm::vec3(0.0f, 0.0f, 0.0f);

    Model::updateUniformBuffer(device, currentImage);
}

std::ostream &operator<<(std::ostream &stream, const glm::vec3 &vec) {
    stream << vec.x << " " << vec.y << " " << vec.z;
    return stream;
}
