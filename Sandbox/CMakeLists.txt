cmake_minimum_required(VERSION 3.30)

project(Sandbox
		VERSION 0.0.0
		DESCRIPTION "Sandbox for TIMGE testing."
)

set(SANDBOX_NAME "Sandbox")
set(SANDBOX_SRCDIR "${CMAKE_SOURCE_DIR}/Sandbox")

add_definitions(-DTIMGE_ENABLE_IMGUI)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE EXE_SRC CONFIGURE_DEPENDS "${SANDBOX_SRCDIR}/src/*.cpp")

add_executable("${SANDBOX_NAME}")

target_sources("${SANDBOX_NAME}" PRIVATE ${EXE_SRC})
target_include_directories("${SANDBOX_NAME}" PRIVATE "${SANDBOX_SRCDIR}/include/")
target_link_directories("${SANDBOX_NAME}" PRIVATE "${SANDBOX_SRCDIR}/lib")
target_link_directories("${SANDBOX_NAME}" PRIVATE "${SANDBOX_SRCDIR}/vendor")
target_link_libraries("${SANDBOX_NAME}" PRIVATE TIMGE)

add_custom_target(sandbox_comp_commands
    ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/compile_commands.json" "${SANDBOX_SRCDIR}"
)
