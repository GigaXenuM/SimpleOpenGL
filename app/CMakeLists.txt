cmake_minimum_required(VERSION 3.20)

# Add header files
set(HEADER_FILES
    src/mainwindow.h

    src/iapplication.h
    src/application.h

    src/utils/stb-image/stb_image.h
    src/utils/internal-id/internalid.h
    src/utils/file-loader/fileloader.h

    src/content/contentcontroller.h
    src/content/shadercontext.h

    src/scene/scenecontroller.h
    src/scene/camera/camera.h
    src/scene/items/iitem.h
    src/scene/items/graphicsitem.h

    src/GPU-tools/igpuidentifier.h
    src/GPU-tools/shader.h
    src/GPU-tools/iprogram.h
    src/GPU-tools/program.h
    src/GPU-tools/gpucontext.h
    src/GPU-tools/shadertype.h

    src/model/modelcontroller.h
    src/model/vertex.h
    src/model/mesh.h
    src/model/item/iitem.h
    src/model/item/item.h
    src/model/obj-loader/objloader.h
    src/model/obj-loader/datatype.h

    src/event/event.h
    src/event/eventhandler.h
    src/event/keyevents/keyboard.h
    src/event/keyevents/keyactionevent.h
    src/event/keyevents/keypressevent.h
    src/event/keyevents/keyreleaseevent.h
    src/event/mouseevents/mouseactionevent.h
    src/event/mouseevents/mousepressevent.h
    src/event/mouseevents/mousemoveevent.h
    src/event/mouseevents/mousereleaseevent.h
    src/event/mouseevents/mouse.h
)

# Add source files
set(SOURCE_FILES
    src/main.cpp

    src/mainwindow.cpp

    src/application.cpp

    src/utils/stb-image/stb_image.cpp
    src/utils/internal-id/internalid.cpp
    src/utils/file-loader/fileloader.cpp

    src/GPU-tools/shader.cpp
    src/GPU-tools/program.cpp

    src/content/contentcontroller.cpp
    src/content/shadercontext.cpp

    src/scene/scenecontroller.cpp
    src/scene/camera/camera.cpp
    src/scene/items/graphicsitem.cpp

    src/model/modelcontroller.cpp
    src/model/mesh.cpp
    src/model/item/item.cpp
    src/model/obj-loader/objloader.cpp

    src/event/eventhandler.cpp
    src/event/keyevents/keyactionevent.cpp
    src/event/keyevents/keypressevent.cpp
    src/event/keyevents/keyreleaseevent.cpp
    src/event/mouseevents/mouseactionevent.cpp
    src/event/mouseevents/mousepressevent.cpp
    src/event/mouseevents/mousemoveevent.cpp
    src/event/mouseevents/mousereleaseevent.cpp
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

