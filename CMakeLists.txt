cmake_minimum_required(VERSION 3.20)

project(SimpleOGL)

add_subdirectory(${CMAKE_SOURCE_DIR}/app)

include_directories(
    "${CMAKE_SOURCE_DIR}/library/include"
)

set(GLFW_LIBRARY "${CMAKE_SOURCE_DIR}/library/lib/glfw3.lib")
set(SOIL_LIBRARY "${CMAKE_SOURCE_DIR}/library/lib/soil.lib")

# GLAD
add_library(GLAD "${CMAKE_SOURCE_DIR}/library/lib/glad.c")

target_link_libraries(${PROJECT_NAME}
        ${GLFW_LIBRARY}
        ${SOIL_LIBRARY}
        opengl32
        GLAD
)
