include(../cmake/GoogleTest.cmake)  # Подключаем GTest

enable_testing()

add_executable(test_runner tests.cpp)
target_link_libraries(test_runner PRIVATE gtest gtest_main)

add_test(NAME GoogleTests COMMAND test_runner)
