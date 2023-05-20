cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(client)
set(CMAKE_AUTOMOC ON)

SET(BOOST_LIB "C:/Users/User/prog/boost/include" CACHE PATH "Location of library")
set(CMAKE_PREFIX_PATH "C:/Users/User/prog/qq/Qt/5.12.12/mingw73_64/lib/cmake")

include_directories( /
    ${CMAKE_CURRENT_SOURCE_DIR}/include /
    ${BOOST_LIB} /
    include /
    )

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/Client.cpp
        include/Exceptions.hpp
        include/TaskInfo.hpp

        src/MainWindow.cpp
        include/MainWindow.hpp
        ui/mainwindow.ui

        src/ProblemTypeWindow.cpp
        include/ProblemTypeWindow.hpp
        ui/problemtypewindow.ui

        src/UsageWindow.cpp
        include/UsageWindow.hpp
        ui/usagewindow.ui

        src/SolutionWindow.cpp
        include/SolutionWindow.hpp
        ui/solutionwindow.ui

        include/UI_MainWindow.hpp
        include/UI_SolutionWindow.hpp
        include/UI_ProblemTypeWindow.hpp
        include/UI_UsageWindow.hpp

        include/ProblemType.hpp
        include/Client.hpp
        include/Exceptions.hpp
)

add_executable(client /
            ${PROJECT_SOURCES} /
)

target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ws2_32)
