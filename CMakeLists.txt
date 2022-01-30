cmake_minimum_required(VERSION 3.8)

set(EngineNative "E:/EG/engine-native")
set(PetitEngine "petitEngine")
set(CMAKE_CXX_STANDARD 17)
project(${PetitEngine} CXX)
if(${CMAKE_SIZEOF_VOID_P} STREQUAL "8")
set(platform "x64")
else()
set(platform "x86")
endif()



add_library(glew SHARED IMPORTED GLOBAL)
set_target_properties(glew PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.dll
	IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.lib
)
add_library(glad STATIC IMPORTED GLOBAL)
set_target_properties(glad PROPERTIES
	IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/lib/glad.lib
	IMPORTED_LOCATION_DEBUG  ${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/debug/lib/glad.lib
)
add_library(glfw SHARED IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.dll
	IMPORTED_IMPLIB  ${CMAKE_CURRENT_LIST_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib
)

set(SHADER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/shaders/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/include/shaders/Shader.cpp
)
set(IMAGE_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/image/stb_image.h
	${CMAKE_CURRENT_LIST_DIR}/include/image/Image.h
)
set(RENDER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/render/Texture.h
	${CMAKE_CURRENT_LIST_DIR}/include/render/Texture.cpp
)

set(MATH_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/math/Math.h
	${CMAKE_CURRENT_LIST_DIR}/include/math/Math.cpp
)

set(UTILS_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/utils/Macros.h
)

add_library(PETIT_ENGINE STATIC
	${SHADER_SOURCES}
	${RENDER_SOURCES}
	${MATH_SOURCES}
	${IMAGE_SOURCES}
)

target_link_libraries(PETIT_ENGINE PUBLIC 
	opengl32
	glfw
	glad
)

target_include_directories(PETIT_ENGINE PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/glm/x64-windows/include
	${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/include
	${CMAKE_CURRENT_LIST_DIR}/assimp
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}/glew/include
	${CMAKE_CURRENT_LIST_DIR}/glfw-3.3.bin.WIN64/include
)

add_executable(opengl-001
	${CMAKE_CURRENT_LIST_DIR}/include/courses/001/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/courses/cbFunctions.cpp
)
target_link_libraries(opengl-001 PUBLIC
	PETIT_ENGINE
)
target_include_directories(opengl-001 PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
)
