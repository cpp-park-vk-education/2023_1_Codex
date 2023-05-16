cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(server)

set(CMAKE_CXX_FLAGS "-Wall -pthread")

include_directories(/
        include /
        ${BOOST_LIB} /
        )

add_executable(server /
        src/ArithmeticTask.cpp /
        src/CombinatoricsTask.cpp /
        src/DifferentiationTask.cpp /
        src/EqSystemsTask.cpp /
        src/EquationsTask.cpp /
        src/IntegrationTask.cpp /
        src/MatStatSequenceTask.cpp /
        src/MatrixTask.cpp /

        src/TaskSearcher.cpp /
        src/TaskHandler.cpp /
        src/RequestHandler.cpp /

        src/Session.cpp /
        src/Listener.cpp /
        src/Server.cpp /
        src/main.cpp /
        )

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
