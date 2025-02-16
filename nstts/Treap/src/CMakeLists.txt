cmake_minimum_required(VERSION 3.29)
add_library(treap_src STATIC Treap.cpp Treap.h)
target_include_directories(treap_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})