macro(set_external_windows mexternal CWD)
	add_library(glew SHARED IMPORTED GLOBAL)
	set_target_properties(glew PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CWD}/include/Windows/glew
		IMPORTED_LOCATION ${CWD}/libs/Windows/glew/glew32.dll
		IMPORTED_IMPLIB ${CWD}/libs/Windows/glew/glew32.lib
	)

	add_library(glfw SHARED IMPORTED GLOBAL)
	set_target_properties(glfw PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CWD}/include/Windows/glfw3
		IMPORTED_LOCATION ${CWD}/libs/Windows/glfw3/glfw3.dll
		IMPORTED_IMPLIB  ${CWD}/libs/Windows/glfw3/glfw3dll.lib
	)

	add_library(assimp SHARED IMPORTED GLOBAL)
	set_target_properties(assimp PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CWD}/include/Windows/assimp
		IMPORTED_LOCATION ${CWD}/libs/Windows/assimp/assimp-vc141-mt.dll
		IMPORTED_IMPLIB  ${CWD}/libs/Windows/assimp/assimp-vc141-mt.lib
	)

	add_library(glad STATIC IMPORTED GLOBAL)
	set_target_properties(glad PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CWD}/include/Windows/glad
		IMPORTED_LOCATION ${CWD}/libs/Windows/glad/glad.lib
	)
	target_include_directories(${mexternal} PUBLIC
		${CWD}/include/Windows/glm
	)
	target_link_libraries(${mexternal} PUBLIC
		glad
		# glew
		glfw
		assimp
		opengl32
	)

	file(GLOB_RECURSE WINDOWS_DLLS
		${CWD}/libs/Windows/*.dll
	)

	foreach(item ${WINDOWS_DLLS})
		get_filename_component(filename ${item} NAME)
		get_filename_component(abs ${item} ABSOLUTE)
		add_custom_command(
			TARGET ${mexternal} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different 
					${abs} 
					$<TARGET_FILE_DIR:${mexternal}>/${filename}
		)
	endforeach()
	
endmacro()

macro(set_external_mac mexternal)
	add_library(glew STATIC IMPORTED GLOBAL)
	set_target_properties(glew PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CWD}/include/Mac/glew
		IMPORTED_LOCATION ${CWD}/libs/Mac/libGLEW.a
	)
	add_library(glfw SHARED IMPORTED GLOBAL)
	set_target_properties(glfw PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CWD}/include/Mac/glfw3
		IMPORTED_LOCATION ${CWD}/libs/Mac/libglfw.3.3.dylib
	)
	add_library(assimp SHARED IMPORTED GLOBAL)
	set_target_properties(assimp PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CWD}/include/Mac/assimp
		IMPORTED_LOCATION ${CWD}/libs/Mac/libassimp.5.2.0.dylib
	)
	target_include_directories(${mexternal} PUBLIC
		${CWD}/include/Mac/glm
		${CWD}/include/Mac/glad
	)

	target_link_libraries(${mexternal} PUBLIC
		# glew
		glfw
		assimp
		"-framework OpenGL" 
	)

endmacro()




