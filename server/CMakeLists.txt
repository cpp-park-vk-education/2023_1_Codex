cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(server)

set(CMAKE_CXX_FLAGS "-Wall -pthread")

include_directories(/
        include /
        )

add_executable(
        )

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()