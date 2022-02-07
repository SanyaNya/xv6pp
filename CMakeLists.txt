cmake_minimum_required(VERSION 3.20)

project(xv6pp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_subdirectory(bootloader)

add_executable(kernel.bin kernel.cpp)

target_compile_options(kernel.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        ${CXX_OPTIMIZATION_SIZE_FLAGS};
        ${CXX_FREESTANDING_FLAG};
        ${CXX_NO_EXCEPTIONS_FLAG};
        ${CXX_NO_RTTI_FLAG};
        ${CXX_PIPE};
        ${CXX_WALL_WEXTRA_WERROR_FLAGS}>)

#linker flags
target_link_options(kernel.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${CXX_NO_STDLIB_FLAG}>)

target_cxx_linker_script(kernel.bin
    ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

include(ExternalProject)
ExternalProject_Add(image_creator
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/image_creator
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/kernel.img
    DEPENDS boot.bin kernel.bin image_creator
    COMMAND ${CMAKE_BINARY_DIR}/bin/create_image ${CMAKE_BINARY_DIR}/bootloader/boot.bin ${CMAKE_BINARY_DIR}/kernel.bin ${CMAKE_BINARY_DIR}/kernel.img)

add_custom_target(kernel_image ALL DEPENDS ${CMAKE_BINARY_DIR}/kernel.img)

