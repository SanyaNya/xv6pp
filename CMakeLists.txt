cmake_minimum_required(VERSION 3.20)

project(xv6pp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libcpp)

add_subdirectory(bootloader)
add_subdirectory(kernel)

#Load image_creator
include(ExternalProject)
ExternalProject_Add(image_creator
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/image_creator
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})

#Concat bootblock and kernel
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/kernel.img
    DEPENDS boot.bin kernel.bin image_creator
    COMMAND ${CMAKE_BINARY_DIR}/bin/create_image
    ${CMAKE_BINARY_DIR}/bootloader/boot.bin ${CMAKE_BINARY_DIR}/kernel/kernel.bin ${CMAKE_BINARY_DIR}/kernel.img)

add_custom_target(kernel_image ALL DEPENDS ${CMAKE_BINARY_DIR}/kernel.img)

