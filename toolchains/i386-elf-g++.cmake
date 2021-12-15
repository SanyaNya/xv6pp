set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION i386-elf)

set(CMAKE_C_COMPILER i386-elf-gcc)
set(CMAKE_CXX_COMPILER i386-elf-g++)

#Don`t check compiler
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(CXX_OPTIMIZATION_DEBUG_FLAGS      -O0;-g3)
set(CXX_OPTIMIZATION_STANDARD_FLAGS   -O2)
set(CXX_OPTIMIZATION_AGGRESSIVE_FLAGS -O3)
set(CXX_OPTIMIZATION_SIZE_FLAGS       -Os)

set(CXX_NO_STDLIB_FLAG           -nostdlib)
set(CXX_FREESTANDING_FLAG        -ffreestanding)
set(CXX_NO_RED_ZONE_FLAG         -mno-red-zone)
set(CXX_NO_EXCEPTIONS_FLAG       -fno-exceptions)
set(CXX_NO_RTTI_FLAG             -fno-rtti)
set(CXX_WALL_WEXTRA_WERROR_FLAGS -Wall;-Wextra;-Werror)

function(target_cxx_linker_script TARGET LINKER_SCRIPT)
    set_target_properties(${TARGET} PROPERTIES
        LINK_FLAGS "-T ${LINKER_SCRIPT}"
        LINK_DEPENDS ${LINKER_SCRIPT})
endfunction()
