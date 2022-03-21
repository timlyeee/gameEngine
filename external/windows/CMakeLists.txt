set(ENGINE_EXTERNAL external)
add_library(glew SHARED IMPORTED GLOBAL)
set_target_properties(glew PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/glew/include
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.dll
	IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.lib
)

add_library(glfw SHARED IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/glfw/include
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glfw/lib/glfw3.dll
	IMPORTED_IMPLIB  ${CMAKE_CURRENT_LIST_DIR}/glfw/lib/glfw3dll.lib
)

add_library(assimp SHARED IMPORTED GLOBAL)
set_target_properties(assimp PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/assimp
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/assimp/x64/assimp-vc141-mt.dll
	IMPORTED_IMPLIB  ${CMAKE_CURRENT_LIST_DIR}/assimp/x64/assimp-vc141-mt.lib
)

add_library(glad STATIC IMPORTED GLOBAL)
set_target_properties(glad PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/include
	IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/glad/x64-windows/lib/glad.lib
)

add_library(${ENGINE_EXTERNAL} STATIC
	${CMAKE_CURRENT_LIST_DIR}/Macros.cpp 
	${CMAKE_CURRENT_LIST_DIR}/Macros.h
)
target_link_libraries(${ENGINE_EXTERNAL} PUBLIC
	glad
	# glew
	glfw
	assimp
	opengl32
)

target_include_directories(${ENGINE_EXTERNAL} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/glm/x64-windows/include
)


add_custom_command(TARGET ${ENGINE_EXTERNAL} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/glew/${platform}/glew32.dll $<TARGET_FILE_DIR:${ENGINE_EXTERNAL}>/glew32.dll
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/glfw/lib/glfw3.dll $<TARGET_FILE_DIR:${ENGINE_EXTERNAL}>/glfw3.dll
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/assimp/x64/assimp-vc141-mt.dll $<TARGET_FILE_DIR:${ENGINE_EXTERNAL}>/assimp-vc141-mt.dll
	# COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/assimp/x64/assimp-vc141-mt.dll $<TARGET_FILE_DIR:${ENGINE_EXTERNAL}>/assimp-vc141-mt.dll
	COMMAND ${CMAKE_COMMAND} -E echo "Copying resources done!"
)