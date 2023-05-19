cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

SET(BOOST_LIB "C:/Users/User/prog/boost/include" CACHE PATH "Location of library")

option(BUILD_TESTS "build test")
if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(client/tests)
endif ()

add_subdirectory(server)
