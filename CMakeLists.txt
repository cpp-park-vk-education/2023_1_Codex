cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(PaddleOCR/deploy/cpp_infer)

option(BUILD_TESTS "build test")
#if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
#endif ()

add_subdirectory(server)
