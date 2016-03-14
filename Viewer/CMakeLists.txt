project(Viewer)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)


set(HEADER utility.h)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
LINK_LIBRARIES(${OPENGL_LIBRARIES})

include_directories("usr/include/GLFW")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})


set(CMAKE_CXX_FLAGS "-std=c++11")

# pour mettre en debug -DCMAKE_BUILD_TYPE=Debug en argument a cmake
