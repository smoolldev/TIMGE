cmake_minimum_required(VERSION 3.27)

option(PRODUCTION_BUILD "Make this a production build" OFF)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(Sandbox
		VERSION 0.0.1
		DESCRIPTION "CMake boilerplate for executables."
)

file(GLOB_RECURSE EXE_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 20)

if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 

	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) 

else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 

endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${EXE_SRC})

if(MSVC) # If using the VS compiler...
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
	
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/lib")

#target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw 
#	glad stb_image stb_truetype gl2d raudio imgui safeSave profilerLib enet glui)

#enet not working yet on linux for some reason
#target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw 
#	glad stb_image stb_truetype gl2d raudio imgui safeSave profilerLib glui)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE TIMGE glfw3 glad)
