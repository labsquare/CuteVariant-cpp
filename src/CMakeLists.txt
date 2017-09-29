cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(cutevariant VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Qt prefix : Change it !! 
#set(CMAKE_PREFIX_PATH "/media/sacha/Linux_data/Qt/5.9.1/gcc_64")

# Find Qt package 
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(ZLIB REQUIRED)

# Test Qt version 
if (Qt5Widgets_VERSION VERSION_LESS 5.9.0)
	message(FATAL_ERROR "Minimum supported Qt5 version is 5.9.0!")
endif()


add_subdirectory(quazip)
add_subdirectory(lib)
add_subdirectory(qscintilla/Qt4Qt5)
add_subdirectory(app)

