cmake_minimum_required(VERSION 3.20)

# Add header files
set(HEADER_FILES
    src/mainwindow.h

    src/iapplication.h
    src/application.h

    src/tools/color.h    
    src/tools/texture.h
    src/tools/vertex.h
    src/tools/stb_image.h
    src/tools/texturetype.h

    src/scene/scene.h
    src/model/mesh/mesh.h
    src/scene/camera/camera.h
    src/scene/items/iitem.h
    src/scene/items/graphicsitem.h

    src/shader/ishaderwrapper.h
    src/shader/shader.h
    src/shader/program.h

    src/model/fileLoader/fileloader.h
    src/model/modelitem/modelitem.h
    src/model/mesh/mesh.h

    src/keyboard/keyboard.h

    src/event/event.h
    src/event/mouseevents/mousemoveevent.h
    src/event/keyevents/keypressevent.h
)

# Add source files
set(SOURCE_FILES
    src/main.cpp

    src/mainwindow.cpp

    src/application.cpp

    src/tools/stb_image.cpp

    src/shader/shader.cpp
    src/shader/program.cpp

    src/scene/scene.cpp
    src/scene/camera/camera.cpp
    src/scene/items/graphicsitem.cpp

    src/model/fileLoader/fileloader.cpp
    src/model/modelitem/modelitem.cpp
    src/model/mesh/mesh.cpp

    src/event/mouseevents/mousemoveevent.cpp
    src/event/keyevents/keypressevent.cpp
)

include_directories(
    "${CMAKE_SOURCE_DIR}/app/src"
)

# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    add_custom_target(copy_resources ALL
       ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/bin/resources
       DEPENDS ${PROJECT_NAME}
       )
endif()

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

