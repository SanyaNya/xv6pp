cmake_minimum_required(VERSION 3.20)

project(bootloader CXX ASM_NASM)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(boot.bin bootloader.asm x86.asm bootmain.cpp)

target_compile_options(boot.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        ${CXX_OPTIMIZATION_SIZE_FLAGS};
        ${CXX_FREESTANDING_FLAG};
        ${CXX_NO_RED_ZONE_FLAG};
        ${CXX_NO_EXCEPTIONS_FLAG};
        ${CXX_NO_RTTI_FLAG};
        ${CXX_WALL_WEXTRA_WERROR_FLAGS}>)

#linker flags
target_link_options(boot.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${CXX_NO_STDLIB_FLAG}>)

target_cxx_linker_script(boot.bin
    ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)
