set(APP 001_init_render_pipeline)

set(SHADER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/shaders/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/shaders/Shader.cpp
)

set(VIEW_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/view/View.h
	${CMAKE_CURRENT_LIST_DIR}/view/View.cpp
	${CMAKE_CURRENT_LIST_DIR}/view/GLFWCallback.cpp
)

add_executable(${APP}
	${SHADER_SOURCES}
	${VIEW_SOURCES}
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)
target_link_libraries(${APP} 
	${MEXTERNAL}
)

# copy resources
add_custom_command(
	TARGET ${APP} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_CURRENT_LIST_DIR}/resources 
			$<TARGET_FILE_DIR:${APP}>
)