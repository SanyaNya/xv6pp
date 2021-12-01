cmake_minimum_required(VERSION 3.20)

project(bootloader CXX ASM_NASM)

include(ExternalProject)

ExternalProject_Add(bootsector_creator 
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bootsector_creator
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(boot.bin bootloader.asm bootmain.cpp)

target_compile_options(boot.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        -Os;
        -ffreestanding;
        -mno-red-zone;
        -fno-exceptions;
        -fno-rtti;
        -Wall;
        -Wextra;
        -Werror>)

#linker flags
set_target_properties(boot.bin PROPERTIES
    LINK_FLAGS "-nostdlib -T ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
    LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

add_custom_target(bootsector ALL DEPENDS bootsector.bin)

add_custom_command(
    OUTPUT bootsector.bin
    DEPENDS boot.bin bootsector_creator
    COMMAND ${CMAKE_BINARY_DIR}/bin/create_bootsector boot.bin bootsector.bin)
