set_property(GLOBAL PROPERTY USE_FOLDERS On)
cmake_minimum_required(VERSION 3.8)

set(MENGINE "learnopengl_to_renderpipeline")

set(CMAKE_CXX_STANDARD 17)

project(${MENGINE} CXX)

# External module
include(${CMAKE_CURRENT_LIST_DIR}/external/CMakeLists.txt)

set(MEXTERNAL engine_external)
add_library(${MEXTERNAL} STATIC
	${CMAKE_CURRENT_LIST_DIR}/external/Macros.h
	${CMAKE_CURRENT_LIST_DIR}/external/Macros.cpp
)
if(WIN32)
	set_external_windows(${MEXTERNAL} ${CMAKE_CURRENT_LIST_DIR}/external)
elseif(APPLE)
	set_external_mac(${MEXTERNAL} ${CMAKE_CURRENT_LIST_DIR}/external)
endif()

# course 1
include(${CMAKE_CURRENT_LIST_DIR}/courses/001_init_render_pipeline/CMakeLists.txt)

# # course 2
# include(${CMAKE_CURRENT_LIST_DIR}/courses/002/CMakeLists.txt)

# # course 3
# include(${CMAKE_CURRENT_LIST_DIR}/courses/003/CMakeLists.txt)

# # course 4
# include(${CMAKE_CURRENT_LIST_DIR}/courses/004_camera/CMakeLists.txt)

# # course 5
# include(${CMAKE_CURRENT_LIST_DIR}/courses/005_color/CMakeLists.txt)

# # course 6
# include(${CMAKE_CURRENT_LIST_DIR}/courses/006_basicLighting/CMakeLists.txt)

# # course 7
# include(${CMAKE_CURRENT_LIST_DIR}/courses/007_material/CMakeLists.txt)

# # course 8
# include(${CMAKE_CURRENT_LIST_DIR}/courses/008_reflect/CMakeLists.txt)