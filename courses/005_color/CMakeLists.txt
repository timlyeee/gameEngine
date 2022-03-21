set(APP_NAME course005_color)

set(SHADER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/shaders/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/shaders/Shader.cpp
)
set(IMAGE_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/image/stb_image.h
)
set(RENDER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/renderer/Texture.h
	${CMAKE_CURRENT_LIST_DIR}/renderer/Texture.cpp
)

set(VIEW_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/view/View.h
	${CMAKE_CURRENT_LIST_DIR}/view/View.cpp
	${CMAKE_CURRENT_LIST_DIR}/view/GLFWCallback.h
	${CMAKE_CURRENT_LIST_DIR}/view/Camera.h	
)

add_executable(${APP_NAME}
	${SHADER_SOURCES}
	${RENDER_SOURCES}
	${IMAGE_SOURCES}
	${VIEW_SOURCES}
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/image/stb_image.h
)
target_link_libraries(${APP_NAME} 
	${ENGINE_EXTERNAL}
)


set_target_properties(
    ${APP_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

