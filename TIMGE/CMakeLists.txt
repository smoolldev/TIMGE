cmake_minimum_required(VERSION 3.30)

project(TIMGE
		VERSION 0.0.1
		DESCRIPTION "Two Idiots Making a Game Engine in C++ (of course)."
		LANGUAGES CXX
)

option(TIMGE_ENABLE_IMGUI "Enable ImGUI for use with engine" ON)

if (TIMGE_ENABLE_IMGUI)
        add_definitions(-DTIMGE_ENABLE_IMGUI)
endif()

set(TIMGE_NAME "TIMGE")
set(TIMGE_SRCDIR "${CMAKE_SOURCE_DIR}/TIMGE")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_LIBRARY_TYPE OBJECT)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb_image)

if (TIMGE_ENABLE_IMGUI)
        add_library(
                imgui OBJECT EXCLUDE_FROM_ALL
                vendor/imgui/imgui.cpp
                vendor/imgui/imgui.h
                vendor/imgui/imgui_demo.cpp
                vendor/imgui/imgui_draw.cpp
                vendor/imgui/imgui_internal.h
                vendor/imgui/imgui_widgets.cpp
                vendor/imgui/imstb_rectpack.h
                vendor/imgui/imstb_textedit.h
                vendor/imgui/imstb_truetype.h
                vendor/imgui/imconfig.h
                vendor/imgui/imgui_tables.cpp
                vendor/imgui/imgui_internal.h
                vendor/imgui/backends/imgui_impl_glfw.h
                vendor/imgui/backends/imgui_impl_glfw.cpp
                vendor/imgui/backends/imgui_impl_opengl3.h
                vendor/imgui/backends/imgui_impl_opengl3.cpp
        )
include_directories(imgui ${TIMGE_SRCDIR}/vendor/glfw/include vendor/imgui vendor/imgui/backends)
target_link_libraries(imgui PRIVATE glfw)
endif()

file(GLOB_RECURSE LIB_SRC CONFIGURE_DEPENDS "${TIMGE_SRCDIR}/src/*.cpp")

add_library("${TIMGE_NAME}" STATIC)

if (TIMGE_ENABLE_IMGUI)
        target_sources("${TIMGE_NAME}" PRIVATE ${LIB_SRC}
            $<TARGET_OBJECTS:glfw>
            $<TARGET_OBJECTS:glad>
            $<TARGET_OBJECTS:stb_image>
            $<TARGET_OBJECTS:imgui>
        )
else()
        target_sources("${TIMGE_NAME}" PRIVATE ${LIB_SRC}
            $<TARGET_OBJECTS:glfw>
            $<TARGET_OBJECTS:glad>
            $<TARGET_OBJECTS:stb_image>
        )
endif()

target_include_directories("${TIMGE_NAME}" PRIVATE "${TIMGE_SRCDIR}/include/")
if (TIMGE_ENABLE_IMGUI)
    target_link_libraries("${TIMGE_NAME}" PRIVATE glfw glad stb_image imgui)
else()
    target_link_libraries("${TIMGE_NAME}" PRIVATE glfw glad stb_image)
endif()

# Copy TIMGE headers to Sandbox/include
add_custom_target(copy_includes
    ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${TIMGE_SRCDIR}/include/TIMGE" "${CMAKE_SOURCE_DIR}/Sandbox/include/TIMGE"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${TIMGE_SRCDIR}/vendor/glfw/include/GLFW" "${CMAKE_SOURCE_DIR}/Sandbox/include/GLFW"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${TIMGE_SRCDIR}/vendor/glad/include/glad" "${CMAKE_SOURCE_DIR}/Sandbox/include/glad"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${TIMGE_SRCDIR}/vendor/glad/include/KHR" "${CMAKE_SOURCE_DIR}/Sandbox/include/KHR"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${TIMGE_SRCDIR}/vendor/stb_image/include/stb_image" "${CMAKE_SOURCE_DIR}/Sandbox/include/stb_image"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${TIMGE_SRCDIR}/vendor/imgui/imgui.h" "${CMAKE_SOURCE_DIR}/Sandbox/include/imgui.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${TIMGE_SRCDIR}/vendor/imgui/imgui_internal.h" "${CMAKE_SOURCE_DIR}/Sandbox/include/imgui_internal.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${TIMGE_SRCDIR}/vendor/imgui/imconfig.h" "${CMAKE_SOURCE_DIR}/Sandbox/include/imconfig.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${TIMGE_SRCDIR}/vendor/imgui/imstb_rectpack.h" "${CMAKE_SOURCE_DIR}/Sandbox/include/imstb_rectpack.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${TIMGE_SRCDIR}/vendor/imgui/imstb_textedit.h" "${CMAKE_SOURCE_DIR}/Sandbox/include/imstb_textedit.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${TIMGE_SRCDIR}/vendor/imgui/imstb_truetype.h" "${CMAKE_SOURCE_DIR}/Sandbox/include/imstb_truetype.h"
)

add_custom_target(timge_comp_commands
    ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/compile_commands.json" "${TIMGE_SRCDIR}"
)
