cmake_minimum_required(VERSION 3.14)
add_library(lines_src STATIC Line.cpp Line.h Point.cpp Point.h Triple.cpp Triple.h)
target_include_directories(lines_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
