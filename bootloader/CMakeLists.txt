cmake_minimum_required(VERSION 3.20)

project(xv6pp_bootloader CXX ASM_NASM)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(boot.bin bootloader.asm bootmain.cpp)

target_compile_options(boot.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        ${CXX_OPTIMIZATION_SIZE_FLAGS};
        ${CXX_NO_STACK_PROTECTOR_FLAG};
        ${CXX_NO_EXCEPTIONS_FLAG};
        ${CXX_NO_RTTI_FLAG};
        ${CXX_PIPE};
        ${CXX_WALL_WEXTRA_WERROR_FLAGS}>)

#linker flags
target_link_options(boot.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        ${CXX_NO_STDLIB_FLAG};
        ${CXX_STRIP_BINARY}>)

target_cxx_linker_script(boot.bin
    ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)
