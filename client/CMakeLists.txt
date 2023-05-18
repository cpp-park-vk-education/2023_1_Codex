cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(client)

set(CMAKE_CXX_FLAGS "-Wall -pthread")

include_directories(/
        include /
        ${BOOST_LIB} /
        )

add_executable(client /
        src/client.cpp /
        src/main.cpp /
        )

