set(APP 001_init_render_pipeline)

set(APPLICATION_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/core/application/Application.h
	${CMAKE_CURRENT_LIST_DIR}/core/application/Application.cpp
)
# source_group(application FILES ${APPLICATION_SOURCES})

set(FILESYSTEM_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/core/fileSystem/FileSystem.h
	${CMAKE_CURRENT_LIST_DIR}/core/fileSystem/FileSystem.cpp
)
# source_group(fileSystem FILES ${FILESYSTEM_SOURCES})

set(VIEW_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/core/renderWindow/GLRenderWindow.h
	${CMAKE_CURRENT_LIST_DIR}/core/renderWindow/GLRenderWindow.cpp
	${CMAKE_CURRENT_LIST_DIR}/core/renderWindow/GLFWCallback.h
	${CMAKE_CURRENT_LIST_DIR}/core/renderWindow/GLFWCallback.cpp
)
# source_group(view FILES ${VIEW_SOURCES})

set(RENDERPIPELINE_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/stages/GeometryStage.h
	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/stages/GeometryStage.cpp
	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/stages/RasterizationStage.h
	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/stages/RasterizationStage.cpp

	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/shaders/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/shaders/Shader.cpp
	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/scene/Scene.h
	${CMAKE_CURRENT_LIST_DIR}/renderpipeline/scene/Scene.cpp
)
# source_group(renderpipeline FILES ${RENDERPIPELINE_SOURCES})

set(PROJ_SOURCES
	${RENDERPIPELINE_SOURCES}
	${FILESYSTEM_SOURCES}
	${APPLICATION_SOURCES}
	${VIEW_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX "Source Files" FILES ${PROJ_SOURCES})

add_executable(${APP}
	${RENDERPIPELINE_SOURCES}
	${FILESYSTEM_SOURCES}
	${APPLICATION_SOURCES}
	${VIEW_SOURCES}
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}) #set include directory from root

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