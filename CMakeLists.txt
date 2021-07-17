cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME "petitEngine")
project(${PROJECT_NAME} CXX)

add_library(glew STATIC IMPORTED GLOBAL)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/lib/Release/x64/glew32s.lib
)

add_library(glfw STATIC IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib
)

set(PROJ_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/include/main.cpp
)
add_executable(PROJECT_NAME ${PROJ_SOURCES})


target_link_libraries(PROJECT_NAME PUBLIC 
	glfw 
	glew 
	opengl32)
target_include_directories(PROJECT_NAME PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/glfw-3.3.bin.WIN64/include/GLFW
    ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include                           
)