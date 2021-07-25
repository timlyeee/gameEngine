cmake_minimum_required(VERSION 3.8)

set(PetitEngine "petitEngine")
project(${PetitEngine} CXX)

add_library(glew STATIC IMPORTED GLOBAL)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/lib/Release/x64/glew32s.lib
)

add_library(glfw STATIC IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib
)
add_library(glad STATIC IMPORTED GLOBAL)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/lib/glad.lib
)



set(PROJ_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/include/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/cbFunctions.cpp
)
add_executable(PetitEngine ${PROJ_SOURCES})


target_link_libraries(PetitEngine PUBLIC 
	glfw 
	glew 
	glad
	opengl32)
target_include_directories(PetitEngine PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/glfw-3.3.bin.WIN64/include/GLFW
    ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include/GL        
	${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/include
	${CMAKE_CURRENT_LIST_DIR}/glm/x64-windows/include
	
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PetitEngine})