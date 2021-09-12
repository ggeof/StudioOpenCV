cmake_minimum_required(VERSION 3.9)

project(StudioOpenCV 
        VERSION 0.0.1
        DESCRIPTION "Studio OpenCV for dev algorithm using OpenCV")


#Liste des header
file(GLOB_RECURSE INCLUDES_FILES "src/*.h")
file(GLOB_RECURSE SRCS_FILES "src/*.cpp")

# Opencv
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Executable
add_executable (StudioOpenCV ${SRCS_FILES})
target_link_libraries(StudioOpenCV ${OpenCV_LIBS} stdc++fs)