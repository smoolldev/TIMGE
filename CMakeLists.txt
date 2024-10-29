cmake_minimum_required(VERSION 3.30)

project(TIMGEProject
    VERSION 0.0.1
    DESCRIPTION "Build system for both TIMGE and the sandbox/demo project."
    LANGUAGES CXX
)

add_subdirectory(TIMGE)
add_subdirectory(Sandbox)

execute_process(
    COMMAND find ${CMAKE_SOURCE_DIR}/TIMGE/include/TIMGE ${CMAKE_SOURCE_DIR}/TIMGE/src -type f \( -name "*.hpp" -o -name "*.cpp" \) -exec awk "NF" {} +
    COMMAND wc -l
    OUTPUT_VARIABLE line_count
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_custom_target(print_line_count ALL
    COMMENT "Counting lines of code"
    COMMAND ${CMAKE_COMMAND} -E echo "Total lines of code making up TIMGE: ${line_count}"
)

#message(STATUS "Total non-empty lines of code: ${line_count}")
