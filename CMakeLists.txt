cmake_minimum_required(VERSION 3.14)
project(Echess LANGUAGES CXX)

# Detect OS system
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SYS_WINDOWS TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SYS_LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SYS_MACOSX TRUE)
endif ()

# Conan setup
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

# Set CMakeFlags for compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O3 -std=c++17")

# Specify project include directories and sources files 
include_directories(${PROJECT_SOURCE_DIR}/includes/)
include_directories(${PROJECT_SOURCE_DIR}/includes/vk_wrapper/)
include_directories(${PROJECT_SOURCE_DIR}/includes/scene/)
add_executable(${PROJECT_NAME}
        sources/scene/camera.cpp
        sources/scene/echess.cpp
        sources/scene/pawn.cpp
        sources/vk_wrapper/application.cpp
        sources/vk_wrapper/buffer-manip.cpp
        sources/vk_wrapper/command-buffers.cpp
        sources/vk_wrapper/command-pool.cpp
        sources/vk_wrapper/depth-image.cpp
        sources/vk_wrapper/descriptor-sets.cpp
        sources/vk_wrapper/devices.cpp
        sources/vk_wrapper/framebuffers.cpp
        sources/vk_wrapper/graphics-pipeline.cpp
        sources/vk_wrapper/instance.cpp
        sources/vk_wrapper/mesh.cpp
        sources/vk_wrapper/model.cpp
        sources/vk_wrapper/surface.cpp
        sources/vk_wrapper/swap-chain.cpp
        sources/vk_wrapper/sync-objects.cpp
        sources/vk_wrapper/texture.cpp
        sources/vk_wrapper/uniform-buffers.cpp
        sources/vk_wrapper/window.cpp
        sources/vk_wrapper/utils.cpp
        sources/main.cpp)

# Link Conan libraries
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

find_package(Vulkan REQUIRED)
if (VULKAN_FOUND)
    message(STATUS "Found Vulkan, Including and Linking now")
    # include_directories(${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
endif (VULKAN_FOUND)

# Export compile commands for vscode config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile shaders with a bash script
execute_process(COMMAND bash
        ${PROJECT_SOURCE_DIR}/compile_shader.sh ${PROJECT_SOURCE_DIR} ${CMAKE_BINARY_DIR})

# Config rpath for conan dynamic libraries
if (SYS_MACOSX)
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "${CMAKE_BINARY_DIR}/lib/"
            $<TARGET_FILE:${PROJECT_NAME}>)
endif ()