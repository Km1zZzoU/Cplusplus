include(../cmake/GoogleTest.cmake)


add_executable(test_runner tests.cpp)
target_link_libraries(test_runner gtest gtest_main treap_src)
target_include_directories(test_runner PRIVATE ../src)


enable_testing()
add_test(NAME TreapTests COMMAND test_runner)
