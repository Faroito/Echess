cmake_minimum_required(VERSION 3.14)
project(Echess LANGUAGES CXX)

# Detect OS system
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SYS_WINDOWS TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SYS_LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SYS_MACOSX TRUE)
endif()

# Conan setup
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

# Set CMakeFlags for compile option
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O3 -std=c++17")

# Specify project include directories and sources files 
include_directories(${PROJECT_SOURCE_DIR}/includes/)
add_executable(${PROJECT_NAME}
        sources/main.cpp)

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Link Conan libraries
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

# Export compile commands for vscode config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Config rpath for conan dynamic libraries
if (SYS_MACOSX)
    add_custom_command(TARGET ${PROJECT_NAME} 
        POST_BUILD COMMAND 
        ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "${CMAKE_BINARY_DIR}/lib/"
        $<TARGET_FILE:${PROJECT_NAME}>)
endif()