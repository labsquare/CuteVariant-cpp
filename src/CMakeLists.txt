cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(cutevariant VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Qt prefix : Change it !! 
set(CMAKE_PREFIX_PATH "D:/Qt/5.9.1/mingw53_32")
set(KF5Archive_DIR "C:/karchive/lib/cmake/KF5Archive")



# Find Qt package 
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Concurrent REQUIRED)

if (UNIX)
find_package(KF5Archive REQUIRED)
endif(UNIX)

# Test Qt version 
if (Qt5Widgets_VERSION VERSION_LESS 5.9.0)
	message(FATAL_ERROR "Minimum supported Qt5 version is 5.9.0!")
endif()

message("hello")
message(${CMAKE_PREFIX_PATH})
message(${Qt5Core_DIR})

include_directories(qscintilla/Qt4Qt5)
include_directories(qscintilla/src)

include_directories(qscintilla/include)

include_directories(lib)
include_directories(app)

add_subdirectory(qscintilla/Qt4Qt5)
add_subdirectory(lib)
add_subdirectory(app)

