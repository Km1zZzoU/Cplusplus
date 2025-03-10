cmake_minimum_required(VERSION 3.29)
add_library(sp_src STATIC ScopedPTR.cpp)
target_include_directories(sp_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})