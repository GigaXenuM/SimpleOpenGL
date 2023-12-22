cmake_minimum_required(VERSION 3.20)

project(SimpleOGL)

add_subdirectory(${CMAKE_SOURCE_DIR}/app)

include_directories(
    "${CMAKE_SOURCE_DIR}/app/src"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(libs/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(libs/assimp)
target_link_libraries(${PROJECT_NAME} assimp)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
