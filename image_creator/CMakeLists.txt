cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(image_creator)

add_executable(create_image main.cpp)

install(TARGETS create_image)
