cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)



message("Application ")

message(${Qt5Widgets_VERSION})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

message("hello")
message(${CMAKE_BINARY_DIR})
set(CUTEVARIANT_LINK_LIBS libcutevariant.a)
set(QSCINTILLA2_LINK_LIBS libqscintilla2.a)


link_directories(${CMAKE_BINARY_DIR}/qscintilla/Qt4Qt5)
link_directories(${CMAKE_BINARY_DIR}/lib)



include_directories(resultsview)
include_directories(queryeditor)
include_directories(qfonticon)
include_directories(docks)
include_directories(docks/columns)
include_directories(docks/filters)
include_directories(docks/selections)

file(GLOB_RECURSE SOURCES "*.cpp")

qt5_add_resources(RESOURCE_ADDED icons/icons.qrc)

message(${SOURCES})

add_executable(app ${SOURCES} ${RESOURCE_ADDED})
target_link_libraries(app Qt5::Core)
target_link_libraries(app Qt5::Gui)
target_link_libraries(app Qt5::Widgets)
target_link_libraries(app Qt5::Sql)
target_link_libraries(app Qt5::Concurrent)

target_link_libraries(app ${CUTEVARIANT_LINK_LIBS})
target_link_libraries(app ${QSCINTILLA2_LINK_LIBS})
