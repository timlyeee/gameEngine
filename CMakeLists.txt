cmake_minimum_required(VERSION 3.8)

set(MENGINE "PetitEngine")

set(CMAKE_CXX_STANDARD 17)
project(${MENGINE} CXX)
option(PLATFORM_WINDOWS "is using Windows platform" OFF)
option(PLATFORM_MAC "is using Mac platform" ON)



if(PLATFORM_MAC)
find_package(GLEW 2.2 REQUIRED)
#set(GLFW_DIR "/opt/homebrew/Cellar/glfw/3.3.6/")


set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")

# Path to glew lib
include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)

# Path to glfw lib
include_directories(/opt/homebrew/Cellar/glfw/3.3.6/include)

# Path to glm lib
include_directories(/opt/homebrew/Cellar/glm/0.9.9.8/include)
set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.3.6/lib/libglfw.3.dylib)
find_package(GLFW3)
target_link_libraries(${MENGINE}
    ${GLEW_LIBRARIES}
    ${GLFW_LINK}
    ${GLM_LIBRARIES}
    ${OPENGL_LIBRARIES}
)	
#include(${CMAKE_CURRENT_LIST_DIR}/external/mac/CMakeLists.txt)
elseif(PLATFORM_WINDOWS)
	include(${CMAKE_CURRENT_LIST_DIR}/external/windows/CMakeLists.txt)
endif()

# end engine library

# course 1
set(APP_NAME "course001")

add_executable(${APP_NAME}
	${CMAKE_CURRENT_LIST_DIR}/courses/001/main.cpp
)
target_link_libraries(${APP_NAME} PUBLIC
	${MENGINE}
	${OPENGL_LIBRARIES}
	${GLFW_LIBRARIES}
)


target_include_directories(${APP_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
)
target_compile_definitions(${MENGINE} PUBLIC GL_SILENCE_DEPRECATION)