cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(server)

set(BOOST_LIB "/mnt/c/users/user/prog/boost/include" CACHE PATH "Location of library")
set(ppocrLib_DIR /mnt/c/users/user/prog/CLionProjects/2023_1_Codex/cmake-build-debug/PaddleOCR/deploy/cpp_infer/CMakeFiles/Export/lib/cmake/ppocrLib)

set(CMAKE_CXX_FLAGS "-Wall -pthread")

include_directories(/
        include /
        ${BOOST_LIB} /
        /mnt/c/users/user/prog/CLionProjects/2023_1_Codex/PaddleOCR/deploy/cpp_infer/include /
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

        src/TextRecognizer.cpp /
        src/PredictionConverter.cpp /
        src/TaskSearcher.cpp /
        src/TaskHandler.cpp /
        src/RequestHandler.cpp /

        src/Session.cpp /
        src/SessionManager.cpp /
        src/Listener.cpp /
        src/Server.cpp /
        src/main.cpp /
        )

find_package(ppocrLib REQUIRED CONFIG PATHS ${ppocrLib_DIR})

target_link_libraries(server PUBLIC ppocrLib::ppocrLib)

#if (BUILD_TESTS)
    add_library(serverLib /
            src/ArithmeticTask.cpp /
            src/CombinatoricsTask.cpp /
            src/DifferentiationTask.cpp /
            src/EqSystemsTask.cpp /
            src/EquationsTask.cpp /
            src/IntegrationTask.cpp /
            src/MatStatSequenceTask.cpp /
            src/MatrixTask.cpp /

            src/TextRecognizer.cpp /
            src/PredictionConverter.cpp /
            src/TaskSearcher.cpp /
            src/TaskHandler.cpp /
            src/RequestHandler.cpp /

            src/Session.cpp /
            src/SessionManager.cpp /
            src/Listener.cpp /
            src/Server.cpp /
            )

    find_package(ppocrLib REQUIRED CONFIG PATHS ${ppocrLib_DIR})
    target_link_libraries(serverLib PUBLIC ppocrLib::ppocrLib)

    add_subdirectory(tests)
#endif ()
