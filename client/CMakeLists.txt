cmake_minimum_required(VERSION 3.5)

project(client VERSION 0.1 LANGUAGES CXX)
set(BOOST_LIB "C:/Program Files/Boost/include" CACHE PATH "Location of library")
set(CMAKE_AUTOMOC ON)

 include_directories(/
         ${BOOST_LIB} /
         ${CMAKE_CURRENT_SOURCE_DIR}/include
         include
         )

set(CMAKE_CXX_STANDARD 17)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/client.cpp
        include/exceptions.hpp
        include/taskInfo.hpp

        src/mainwindow.cpp
        include/mainwindow.hpp
        ui/mainwindow.ui

        src/problemtypewindow.cpp
        include/problemtypewindow.hpp
        ui/problemtypewindow.ui

        src/usagewindow.cpp
        include/usagewindow.hpp
        ui/usagewindow.ui

        src/solutionwindow.cpp
        include/solutionwindow.hpp
        ui/solutionwindow.ui

        include/ui_mainwindow.hpp
        include/ui_solutionwindow.hpp
        include/ui_problemtypewindow.hpp
        include/ui_usagewindow.hpp

        include/problemType.hpp
        include/client.hpp
        include/exceptions.hpp

)

add_executable(client
            ${PROJECT_SOURCES}
)

target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  ${BOOST_LIB} ws2_32)
