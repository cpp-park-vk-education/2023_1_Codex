cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

SET(BOOST_LIB "/mnt/c/users/user/prog/boost/include" CACHE PATH "Location of library")

add_subdirectory(server)
add_subdirectory(client)

option(BUILD_TESTS "build tests")
if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif ()
