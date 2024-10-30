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

file(GLOB_RECURSE EXE_SRC CONFIGURE_DEPENDS "${SANDBOX_SRCDIR}/src/*.cpp")

add_executable("${SANDBOX_NAME}")

target_compile_features("${SANDBOX_NAME}" PUBLIC cxx_std_20)
target_sources("${SANDBOX_NAME}" PRIVATE ${EXE_SRC})
target_include_directories("${SANDBOX_NAME}" PRIVATE "${SANDBOX_SRCDIR}/include/")
target_link_directories("${SANDBOX_NAME}" PRIVATE "${SANDBOX_SRCDIR}/lib")
target_link_directories("${SANDBOX_NAME}" PRIVATE "${SANDBOX_SRCDIR}/vendor")
target_link_libraries("${SANDBOX_NAME}" PRIVATE TIMGE)

# Create symbolic link between TIMGE's binary directory and it's source directory
if (EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json" AND NOT EXISTS "${SANDBOX_SRCDIR}/compile_commands.json")
    file(
        CREATE_LINK
            "${CMAKE_BINARY_DIR}/compile_commands.json"
            "${SANDBOX_SRCDIR}/compile_commands.json"
        SYMBOLIC
    )
endif()

# file(
#     GLOB
#         TIMGEHeaders
#             "${CMAKE_SOURCE_DIR}/TIMGE/include/TIMGE"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/glfw/include/GLFW"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/glad/include/glad"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/glad/include/KHR"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/stb_image/include/stb_image"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/imgui/imgui.h"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/imgui/imgui_internal.h"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/imgui/imconfig.h"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/imgui/imstb_rectpack.h"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/imgui/imstb_textedit.h"
#             "${CMAKE_SOURCE_DIR}/TIMGE/vendor/imgui/imstb_truetype.h"
# )
#
# file(
#     GLOB
#         SandboxHeaders
#             "${SANDBOX_SRCDIR}/include"
# )
#
# add_custom_target(copy)
# foreach(header ${TIMGEHeaders})
#     add_custom_command(
#         TARGET
#             copy
#         BUILD
#         COMMAND
#             ${CMAKE_COMMAND} -E
#             copy ${header} "${SANDBOX_SRCDIR}/Sandbox/include"
# )
# endforeach()
# add_dependencies(Sandbox copy)
