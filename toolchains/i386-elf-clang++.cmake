set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION i386)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

#Don`t check compiler
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

add_compile_options($<$<COMPILE_LANGUAGE:CXX>:--target=i386-elf>)
add_link_options($<$<COMPILE_LANGUAGE:CXX>:--target=i386-elf>)

set(CXX_OPTIMIZATION_DEBUG_FLAGS      -O0;-g3)
set(CXX_OPTIMIZATION_STANDARD_FLAGS   -O2)
set(CXX_OPTIMIZATION_AGGRESSIVE_FLAGS -O3)
set(CXX_OPTIMIZATION_SIZE_FLAGS       -Oz;-fomit-frame-pointer)
set(CXX_NO_STDLIB_FLAG           -nostdlib)
set(CXX_FREESTANDING_FLAG        -ffreestanding)
set(CXX_NO_STACK_PROTECTOR_FLAG  -fno-stack-protector)
set(CXX_NO_EXCEPTIONS_FLAG       -fno-exceptions)
set(CXX_NO_RTTI_FLAG             -fno-rtti)
set(CXX_STRIP_BINARY             -s)
set(CXX_PIPE                     -pipe)
set(CXX_WALL_WEXTRA_WERROR_FLAGS -Wall;-Wextra;-Wconversion;-pedantic)

function(target_cxx_linker_script TARGET LINKER_SCRIPT)
    set_target_properties(${TARGET} PROPERTIES
        LINK_FLAGS "-T ${LINKER_SCRIPT}"
        LINK_DEPENDS ${LINKER_SCRIPT})
endfunction()
