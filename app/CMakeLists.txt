cmake_minimum_required(VERSION 3.20)

# Add header files
set(HEADER_FILES
    src/mainwindow.h
    src/iapplication.h
    src/application.h
    src/tools/color.h
    src/fileLoader/fileloader.h
    src/scene/scene.h
    src/shader/ishaderwrapper.h
    src/shader/shader.h
    src/shader/program.h
    src/scene/private/gpudatacontroller/gpudatacontroller.h

    src/scene/camera/camera.h
    src/scene/items/item.h

    src/scene/items/testitem.h
)

# Add source files
set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/application.cpp
    src/fileLoader/fileloader.cpp
    src/scene/scene.cpp
    src/shader/shader.cpp
    src/shader/program.cpp
    src/scene/private/gpudatacontroller/gpudatacontroller.cpp

    src/scene/camera/camera.cpp
    src/scene/items/item.cpp

    src/scene/items/testitem.cpp
)

include_directories(
    "${CMAKE_SOURCE_DIR}/library/include"
    "${CMAKE_SOURCE_DIR}/app/src"
)

# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    add_custom_target(copy_resources ALL
       ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
       DEPENDS ${PROJECT_NAME}
       )
endif()

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

