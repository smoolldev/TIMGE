cmake_minimum_required(VERSION 3.30)

project(TIMGE
		VERSION 0.0.1
		DESCRIPTION "Two Idiots Making a Game Engine in C++ (of course)."
)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

file(GLOB_RECURSE LIB_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library("${CMAKE_PROJECT_NAME}" STATIC)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${LIB_SRC})
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glad glfw)
