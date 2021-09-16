cmake_minimum_required(VERSION 3.9)

project(StudioOpenCV 
        VERSION 0.0.1
        DESCRIPTION "Studio OpenCV for dev algorithm using OpenCV")


#Liste des header
file(GLOB_RECURSE INCLUDES_FILES "src/*.h")
file(GLOB_RECURSE SRCS_FILES "src/*.cpp")

add_definitions(-DPATH_PROJET="${CMAKE_SOURCE_DIR}")

# Opencv
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Gtk
find_package (PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories( ${GTK3_INCLUDE_DIRS} )
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# Executable
add_executable (StudioOpenCV ${SRCS_FILES})
target_link_libraries(StudioOpenCV ${OpenCV_LIBS} ${GTK3_LIBRARIES} stdc++fs pthread)
