set(externalLibs);
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

list(APPEND externalLibs
    glew
    glad
    glfw
)