cmake_minimum_required(VERSION 3.8)

set(MENGINE "PetitEngine")

set(CMAKE_CXX_STANDARD 17)
set(platform x64)
project(${MENGINE} CXX)
option(PLATFORM_WINDOWS "is using Windows platform" OFF)
option(PLATFORM_MAC "is using Mac platform" ON)


if(PLATFORM_MAC)
    include(${CMAKE_CURRENT_LIST_DIR}/external/mac/CMakeLists.txt)
	#target_compile_definitions(${APP_NAME} PUBLIC GL_SILENCE_DEPRECATION)
elseif(PLATFORM_WINDOWS)
	include(${CMAKE_CURRENT_LIST_DIR}/external/windows/CMakeLists.txt)
endif()

# course 1
include(${CMAKE_CURRENT_LIST_DIR}/courses/001/CMakeLists.txt)

# course 2
include(${CMAKE_CURRENT_LIST_DIR}/courses/002/CMakeLists.txt)

# course 3
include(${CMAKE_CURRENT_LIST_DIR}/courses/003/CMakeLists.txt)

# course 4
include(${CMAKE_CURRENT_LIST_DIR}/courses/004_camera/CMakeLists.txt)

# course 5
include(${CMAKE_CURRENT_LIST_DIR}/courses/005_color/CMakeLists.txt)

# course 6
include(${CMAKE_CURRENT_LIST_DIR}/courses/006_basicLighting/CMakeLists.txt)

# course 7
include(${CMAKE_CURRENT_LIST_DIR}/courses/007_material/CMakeLists.txt)

# course 8
include(${CMAKE_CURRENT_LIST_DIR}/courses/008_reflect/CMakeLists.txt)