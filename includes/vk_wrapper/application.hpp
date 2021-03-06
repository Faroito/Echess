//
// Created by Timothée Couble on 25/09/2020.
//

#ifndef APPLICATION_HPP
# define APPLICATION_HPP

#include <unordered_map>

#include "i-application.hpp"

#include "command-pool.hpp"
#include "command-buffers.hpp"
#include "devices.hpp"
#include "framebuffers.hpp"
#include "graphics-pipeline.hpp"
#include "instance.hpp"
#include "libraries.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "swap-chain.hpp"
#include "sync-objects.hpp"
#include "window.hpp"

namespace vk_wrapper {

    /**
     * Application class that inherit from IApplication.
     * Makes call to vulkans abstraction classes.
     */
    class Application : public IApplication {
    public:
        explicit Application(const std::string &appName);
        ~Application();

        void run();

    protected:
        virtual void initModels();

        virtual void onDraw();

        void onMouseMove(double x, double y) override;
        void onMouseDown(int button, int action) override;
        void onMouseScroll(double x, double y) override;
        void onKeyDown(int key, int action) override;

    private:
        void initVulkan();

        void cleanup();
        void cleanupSwapChain();
        void recreateSwapChain();

    protected:
        Window m_window;
        SwapChain m_swapChain;

        Models_t m_models;

    private:
        const std::string m_appName;

        Instance m_instance;
        Devices m_devices;
        GraphicsPipeline m_pipeline;
        CommandPool m_commandPool;
        CommandBuffers m_commandBuffers;
        Framebuffers m_framebuffers;
        SyncObjects m_syncObjects;

        MeshMap_t m_meshes;
    };
};

#endif /* !APPLICATION_HPP */