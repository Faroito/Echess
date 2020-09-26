//
// Created by Timothée Couble on 26/09/2020.
//

#ifndef SYNC_OBJECTS_HPP
# define SYNC_OBJECTS_HPP

#include <vector>

#include "command-buffers.hpp"
#include "devices.hpp"
#include "libraries.hpp"
#include "model.hpp"
#include "swap-chain.hpp"
#include "utils.hpp"

namespace vk_wrapper {

    /**
     * SyncObjects that can be used for coordinating operations
     * by having one operation signal and another operation
     * wait for a fence or semaphore to go from the unsignaled
     * to signaled state.
     *
     * Fences are mainly designed to synchronize your Application
     * itself with rendering operation, whereas semaphores are used
     * to synchronize operations within or across command queues.
     */
    class SyncObjects {
    public:
        SyncObjects() = default;

        void setUp(VkDevice &device, size_t size);
        void cleanUp(VkDevice &device);

        bool drawFrame(Devices &devices, SwapChain &swapChain, Models_t &models,
                       CommandBuffers &buffers, bool isResized);

    private:
        size_t m_currentFrame = 0;
        std::vector<VkSemaphore> m_imageAvailableSemaphores;
        std::vector<VkSemaphore> m_renderFinishedSemaphores;
        std::vector<VkFence> m_inFlightFences;
        std::vector<VkFence> m_imagesInFlight;
    };

}

#endif /* !SYNC_OBJECTS_HPP */
