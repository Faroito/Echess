//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef COMMAND_POOL_HPP
# define COMMAND_POOL_HPP

#include "devices.hpp"
#include "libraries.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * Command pools manage the memory that is used to store
     * the buffers and command buffers are allocated from them.
     */
    class CommandPool {
    public:
        CommandPool() = default;

        void setUp(Devices &devices);
        void cleanUp(VkDevice &device);

        VkCommandPool &get();

    private:
        VkCommandPool m_commandPool = nullptr;

    };

}


#endif /* !COMMAND_POOL_HPP */
