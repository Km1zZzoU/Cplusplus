cmake_minimum_required(VERSION 3.29)
add_library(matrix_src STATIC Matrix.cpp)
target_include_directories(matrix_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})