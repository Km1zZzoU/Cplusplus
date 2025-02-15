cmake_minimum_required(VERSION 3.29)
project(Treap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main main.cpp)

add_subdirectory(src)

target_link_libraries(main treap_src)

add_subdirectory(tests)