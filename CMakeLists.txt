cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

project(graphics)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} app/include /include/glad)

file(GLOB sourcefiles "${CMAKE_SOURCE_DIR}/app/src/*.cpp")

add_library(STB_IMAGE "${CMAKE_SOURCE_DIR}/app/src/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE )

#set(SOURCES app/src/triangle.cpp app/src/LGlad.cpp app/src/LUtils.cpp)

add_executable(graphics  ${sourcefiles})
target_link_libraries(graphics glfw dl ${OPENGL_LIBRARY} ${GLFW_LIBRARY} ${OpenCV_LIBS} ${ASSIMP_LIBRARY})