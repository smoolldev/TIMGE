cmake_minimum_required(VERSION 3.30)

project(TIMGEProject
    VERSION 0.0.1
    DESCRIPTION "Build system for both TIMGE and the sandbox/demo project."
    LANGUAGES CXX
)

add_subdirectory(TIMGE)
add_subdirectory(Sandbox)
