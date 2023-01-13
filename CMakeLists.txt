cmake_minimum_required(VERSION 3.20)

project(SimpleOGL)

add_subdirectory(${CMAKE_SOURCE_DIR}/app)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(3rdparty/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(3rdparty/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(3rdparty/glm)
target_link_libraries(${PROJECT_NAME} glm)

include_directories(
    "${CMAKE_SOURCE_DIR}/3rdparty/soil"
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
