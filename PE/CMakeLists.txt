set(PE)
set(SHADER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/shaders/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/include/shaders/Shader.cpp
)
set(IMAGE_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/image/stb_image.h
	${CMAKE_CURRENT_LIST_DIR}/include/image/Image.h
)
set(RENDER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/render/Texture.h
	${CMAKE_CURRENT_LIST_DIR}/include/render/Texture.cpp
)

set(MATH_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/math/Math.h
	${CMAKE_CURRENT_LIST_DIR}/include/math/Math.cpp
)

set(UTILS_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/utils/Macros.h
)

set(VIEW_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/view/View.h
	${CMAKE_CURRENT_LIST_DIR}/include/view/View.cpp
	${CMAKE_CURRENT_LIST_DIR}/include/view/GLFWCallback.cpp
)

add_library(PE STATIC
	${SHADER_SOURCES}
	${RENDER_SOURCES}
	${MATH_SOURCES}
	${IMAGE_SOURCES}
	${VIEW_SOURCES}
)

if(PLATFORM_MAC)
    include(${CMAKE_CURRENT_LIST_DIR}/../external/mac/CMakeLists.txt)
elseif(PLATFORM_WINDOWS)
	include(${CMAKE_CURRENT_LIST_DIR}/../external/windows/CMakeLists.txt)
endif()


