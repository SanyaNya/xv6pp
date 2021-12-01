set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION i386)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

#Don`t check compiler
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

add_compile_options($<$<COMPILE_LANGUAGE:CXX>:--target=i386-elf>)
add_link_options($<$<COMPILE_LANGUAGE:CXX>:--target=i386-elf>)
