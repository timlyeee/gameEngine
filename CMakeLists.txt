cmake_minimum_required(VERSION 3.8)

set(MENGINE "PetitEngine")

set(CMAKE_CXX_STANDARD 17)
project(${MENGINE} CXX)
option(PLATFORM_WINDOWS "is using Windows platform" OFF)
option(PLATFORM_MAC "is using Mac platform" ON)





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