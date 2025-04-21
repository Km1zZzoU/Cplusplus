cmake_minimum_required(VERSION 3.29)
project(ct)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(${SANITIZER_FLAGS})
add_link_options(${SANITIZER_FLAGS})


add_executable(main main.cpp)