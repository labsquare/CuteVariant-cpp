# App

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CUTEVARIANT_LINK_LIBS libcutevariant.a)
set(QSCINTILLA2_LINK_LIBS libqscintilla2.a)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(resultsview)
include_directories(queryeditor)
include_directories(qfonticon)
include_directories(docks)
include_directories(docks/columns)
include_directories(docks/filters)
include_directories(docks/selections)

include_directories(${CMAKE_SOURCE_DIR}/qscintilla/Qt4Qt5)
include_directories(${CMAKE_SOURCE_DIR}/qscintilla/src)
include_directories(${CMAKE_SOURCE_DIR}/qscintilla/include)
include_directories(${CMAKE_SOURCE_DIR}/cutevariantcore)

# Add all c++ files 
file(GLOB_RECURSE SOURCES "*.cpp")

# Add resources 
qt5_add_resources(RESOURCE_ADDED icons/icons.qrc)

link_directories(${CMAKE_BINARY_DIR})

add_executable(app ${SOURCES} ${RESOURCE_ADDED})

## Link edition 
target_link_libraries(app Qt5::Core)
target_link_libraries(app Qt5::Gui)
target_link_libraries(app Qt5::Widgets)
target_link_libraries(app Qt5::Sql)
target_link_libraries(app Qt5::Concurrent)

target_link_libraries(app ${QUAZIP_LIB_TARGET_NAME})
target_link_libraries(app ${CUTEVARIANT_LINK_LIBS})
target_link_libraries(app ${QSCINTILLA2_LINK_LIBS})

add_dependencies(app ${CMAKE_BINARY_DIR}/${CUTEVARIANT_LINK_LIBS})
add_dependencies(app ${CMAKE_BINARY_DIR}/${QUAZIP_LIB_TARGET_NAME})
add_dependencies(app ${CMAKE_BINARY_DIR}/${QSCINTILLA2_LINK_LIBS})