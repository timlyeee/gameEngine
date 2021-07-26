cmake_minimum_required(VERSION 3.8)

set(PetitEngine "petitEngine")
project(${PetitEngine} CXX)



add_library(assimp SHARED IMPORTED GLOBAL)
set_target_properties(assimp PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/assimp/assimp-vc141-mt.dll
	IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/assimp/assimp-vc141-mt.lib
)
set(PROJ_SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/include/sdlMain.cpp
)
add_executable(PetitEngine 
	${PROJ_SOURCES}
	E:/engine-native/cocos/renderer/gfx-gles2/GLES2Wrangler.cpp
    E:/engine-native/cocos/renderer/gfx-gles3/GLES3Wrangler.cpp
    E:/engine-native/cocos/renderer/gfx-gles-common/gles3w.cpp
    E:/engine-native/cocos/renderer/gfx-gles-common/gles2w.cpp
    E:/engine-native/cocos/renderer/gfx-gles-common/eglw.cpp
)


add_library(SDL2 SHARED IMPORTED GLOBAL)

#set(EXTDIR E:/engine-native/external/win32)
set(EXTDIR E:/engine-native/external/win64)

set_target_properties(SDL2 PROPERTIES
  IMPORTED_LOCATION ${EXTDIR}/libs/SDL2.dll
  IMPORTED_IMPLIB ${EXTDIR}/libs/SDL2.lib
  INTERFACE_INCLUDE_DIRECTORIES ${EXTDIR}/include/sdl2
)

add_library(SDL2Main SHARED IMPORTED GLOBAL)
set_target_properties(SDL2Main PROPERTIES
  IMPORTED_IMPLIB ${EXTDIR}/libs/SDL2main.lib
)

target_include_directories(PetitEngine PUBLIC
    E:/engine-native/external/sources/khronos
    E:/engine-native/cocos/renderer/gfx-gles-common
    E:/engine-native/cocos/renderer/gfx-gles3
    E:/engine-native/cocos/renderer/gfx-gles2
    E:/engine-native/external/sources/EGL
)
target_compile_definitions(PetitEngine PUBLIC
    CC_PLATFORM=1
    CC_PLATFORM_WINDOWS=1
    CC_PLATFORM_MAC_IOS=2
)

target_link_libraries(PetitEngine PUBLIC 

	assimp
	opengl32
    ws2_32 userenv psapi winmm Iphlpapi
    SDL2Main SDL2
    )
target_include_directories(PetitEngine PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/glm/x64-windows/include
	${CMAKE_CURRENT_LIST_DIR}/assimp
	${CMAKE_CURRENT_LIST_DIR}/include


	
)
set(bin_dir ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
add_custom_command(TARGET PetitEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying resources to ${bin_dir}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/SDL2.dll $<TARGET_FILE_DIR:PetitEngine>/SDL2.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/libEGL.dll $<TARGET_FILE_DIR:PetitEngine>/libEGL.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/libGLESv2.dll $<TARGET_FILE_DIR:PetitEngine>/libGLESv2.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/libGLES_CM.dll $<TARGET_FILE_DIR:PetitEngine>/libGLES_CM.dll
    COMMAND ${CMAKE_COMMAND} -E echo "Copying resources done!"
)