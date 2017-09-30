# CUTEVARIANT-CORE

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

message("lib cutevariant ")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(QUAZIP_LINK_LIBS libquazip5.a)

file(GLOB SOURCES "*.cpp")

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})


include_directories(../quazip/quazip)


add_library(cutevariant STATIC ${SOURCES})
target_link_libraries(cutevariant Qt5::Core)
target_link_libraries(cutevariant Qt5::Gui)
target_link_libraries(cutevariant Qt5::Sql)
target_link_libraries(cutevariant Qt5::Concurrent)
target_link_libraries(cutevariant ${QUAZIP_LIB_TARGET_NAME})
