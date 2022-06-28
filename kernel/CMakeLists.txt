cmake_minimum_required(VERSION 3.20)

project(xv6pp_kernel)

add_executable(kernel.bin kernel.cpp)

target_compile_options(kernel.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        ${CXX_OPTIMIZATION_SIZE_FLAGS};
        ${CXX_NO_EXCEPTIONS_FLAG};
        ${CXX_NO_RTTI_FLAG};
        ${CXX_PIPE};
        ${CXX_WALL_WEXTRA_WERROR_FLAGS}>)

#linker flags
target_link_options(kernel.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        ${CXX_NO_STDLIB_FLAG};
        ${CXX_STRIP_BINARY}>)

target_cxx_linker_script(kernel.bin
    ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)
