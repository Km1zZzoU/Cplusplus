cmake_minimum_required(VERSION 3.29)
project(ScopedPTR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SANITIZER_FLAGS "-fsanitize=address,undefined")

add_compile_options(${SANITIZER_FLAGS})
add_link_options(${SANITIZER_FLAGS})


# Note: this CMakeLists is broken : (
add_executable(main main.cpp)

add_subdirectory(src)

target_link_libraries(main sp_src)

add_subdirectory(tests)

option(BUILD_TESTING "Build the tests" ON)

if(BUILD_TESTING)
    enable_testing()
endif()
