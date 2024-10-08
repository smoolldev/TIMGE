# Minimum CMake version required
cmake_minimum_required(VERSION 3.27)

# Project metadata
project(TIMGE
    VERSION 0.0.1
    DESCRIPTION "Two Idiots Making a Game Engine in C++ (of course)"
    LANGUAGES CXX
)

# C++ version and compile commands export
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# GLFW Preprocessor Definitions
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
#set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Finding packages
# find_package()

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

# Source files
file(GLOB_RECURSE lib_src CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Creation of library
add_library("${CMAKE_PROJECT_NAME}" STATIC)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${lib_src})

# Header file (.hpp) directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_SOURCE_DIR}/vendor/glfw/include
)

# Libraries the target is linking against (is using)
target_link_libraries(${PROJECT_NAME}
   PRIVATE
       glfw3
       glad
)

# Properties the target has
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/include/TIMGE/TIMGE.hpp)

# Include a CMake module for installing
# include(GNUInstallDirs)

# Install library and headers in specified directories
# install(TARGETS ${PROJECT_NAME}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/custom/path
# )

# Configure a .pc (pkg-config) file, so including the library in a user project is easy
# configure_file(input/${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

# Install .pc (pkg-config) file to pkgconfig directory
# install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
# )
