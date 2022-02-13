find_package(GLEW 2.2 REQUIRED)
#set(GLFW_DIR "/opt/homebrew/Cellar/glfw/3.3.6/")
find_package(GLFW3)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")

# Path to glew lib
link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)
include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)

# Path to glfw lib
link_directories(/opt/homebrew/Cellar/glfw/3.3.6/lib)
include_directories(/opt/homebrew/Cellar/glfw/3.3.6/include)

# Path to glm lib
link_directories(/opt/homebrew/Cellar/glm/0.9.9.8/lib)
include_directories(/opt/homebrew/Cellar/glm/0.9.9.8/include)

target_link_libraries(${MENGINE} PUBLIC
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLM_LIBRARIES}
    ${OPENGL_LIBRARIES}
    "-framework OpenGL" 
)
