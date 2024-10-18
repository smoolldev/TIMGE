cmake_minimum_required(VERSION 3.30)

project(TIMGESandbox
		VERSION 0.0.0
		DESCRIPTION "Sandbox for TIMGE testing."
)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE EXE_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${EXE_SRC})
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/lib")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE TIMGE glad glfw3 stb_image)
