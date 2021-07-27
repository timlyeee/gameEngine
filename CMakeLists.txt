cmake_minimum_required(VERSION 3.8)

set(EngineNative "E:/engine-native")
set(PetitEngine "petitEngine")

project(${PetitEngine} CXX)
if(${CMAKE_SIZEOF_VOID_P} STREQUAL "8")
set(platform "x64")
else()
set(platform "x86")
endif()





add_library(assimp SHARED IMPORTED GLOBAL)
set_target_properties(assimp PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/assimp/${platform}/assimp-vc141-mt.dll
	IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/assimp/${platform}/assimp-vc141-mt.lib
)
add_library(glew SHARED IMPORTED GLOBAL)
set_target_properties(glew PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.dll
	IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.lib
)
add_library(egl SHARED IMPORTED GLOBAL)
set_target_properties(egl PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/eglLibs/${platform}/libEGL.dll
	IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/eglLibs/${platform}/libEGL.lib
)
add_library(glesv2 SHARED IMPORTED GLOBAL)
set_target_properties(glesv2 PROPERTIES
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/eglLibs/${platform}/libGLESv2.dll
	IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/eglLibs/${platform}/libGLESv2.lib
)
set(PROJ_SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/include/sdlMain.cpp
)
set(EngineNativeGlew 
	${EngineNative}/cocos/renderer/gfx-gles2/GLES2Wrangler.cpp
    ${EngineNative}/cocos/renderer/gfx-gles-common/gles2w.cpp
	${EngineNative}/cocos/renderer/gfx-gles3/GLES3Wrangler.cpp
    ${EngineNative}/cocos/renderer/gfx-gles-common/gles3w.cpp
    ${EngineNative}/cocos/renderer/gfx-gles-common/eglw.cpp
)

add_executable(PetitEngine 
	${PROJ_SOURCES}
	${EngineNativeGlew}
)

## Engine native external
if(${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
set(EXTDIR ${EngineNative}/external/win32)
else()
set(EXTDIR ${EngineNative}/external/win64)
endif()
add_library(SDL2 SHARED IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
  IMPORTED_LOCATION ${EXTDIR}/libs/SDL2.dll
  IMPORTED_IMPLIB ${EXTDIR}/libs/SDL2.lib
  INTERFACE_INCLUDE_DIRECTORIES ${EXTDIR}/include/sdl2
)
add_library(SDL2Main SHARED IMPORTED GLOBAL)
set_target_properties(SDL2Main PROPERTIES
  IMPORTED_IMPLIB ${EXTDIR}/libs/SDL2main.lib
)

## end externals

set(glesDir 
	${EngineNative}/external/sources/khronos
    ${EngineNative}/cocos/renderer/gfx-gles-common
    ${EngineNative}/cocos/renderer/gfx-gles2
	${EngineNative}/cocos/renderer/gfx-gles3
	${EngineNative}/external/sources/EGL
)


target_include_directories(PetitEngine PUBLIC ${glesDir})
target_compile_definitions(PetitEngine PUBLIC
    CC_PLATFORM=1
    CC_PLATFORM_WINDOWS=1
    CC_PLATFORM_MAC_IOS=2
)

target_link_libraries(PetitEngine PUBLIC 
	opengl32
    ws2_32 userenv psapi winmm Iphlpapi
    SDL2Main SDL2
	assimp
	glew
	egl
	glesv2
)

target_include_directories(PetitEngine PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/glm/x64-windows/include
	${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/include
	${CMAKE_CURRENT_LIST_DIR}/assimp
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}/glew/include
)
set(bin_dir ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
add_custom_command(TARGET PetitEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying resources to ${bin_dir}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/SDL2.dll $<TARGET_FILE_DIR:PetitEngine>/SDL2.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/libEGL.dll $<TARGET_FILE_DIR:PetitEngine>/libEGL.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/libGLESv2.dll $<TARGET_FILE_DIR:PetitEngine>/libGLESv2.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXTDIR}/libs/libGLES_CM.dll $<TARGET_FILE_DIR:PetitEngine>/libGLES_CM.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.dll $<TARGET_FILE_DIR:PetitEngine>/glew32.dll
	COMMAND ${CMAKE_COMMAND} -E echo "Copying resources done!"

)