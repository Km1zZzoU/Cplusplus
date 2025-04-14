cmake_minimum_required(VERSION 3.29)
add_library(li_src STATIC limit_instance.cpp)
target_include_directories(li_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})