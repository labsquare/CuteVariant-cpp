cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)


message("lib cutevariant ")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)


file(GLOB SOURCES "*.cpp")

add_library(cutevariant SHARED ${SOURCES})
target_link_libraries(cutevariant Qt5::Core)
target_link_libraries(cutevariant Qt5::Gui)
target_link_libraries(cutevariant Qt5::Sql)
target_link_libraries(cutevariant Qt5::Concurrent)
target_link_libraries(cutevariant KF5::Archive)
