include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Не пересобирать, если GTest уже есть
FetchContent_MakeAvailable(googletest)

# Отключаем установку GTest
set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of GoogleTest" FORCE)
