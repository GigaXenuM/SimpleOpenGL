cmake_minimum_required(VERSION 3.20)

# Add header files
set(HEADER_FILES
    src/mainwindow.h
    src/iapplication.h
    src/application.h
    src/tools/color.h
    src/shaders/shaderloader.h
    src/fileLoader/ifileloader.h
)

# Add source files
set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/application.cpp
    src/shaders/shaderloader.cpp
)

include_directories(
    "${CMAKE_SOURCE_DIR}/library/include"
    "${CMAKE_SOURCE_DIR}/app/src"
)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
