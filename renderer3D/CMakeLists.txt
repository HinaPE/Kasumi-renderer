cmake_minimum_required(VERSION 3.24)
project(Kasumi_Render3D VERSION 2.0.0 DESCRIPTION "Kasumi Renderer 3D" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    message(FATAL_ERROR "Kasumi_Backends is not found")
    return()
endif ()

add_library(Kasumi_Render3D STATIC)
target_sources(Kasumi_Render3D
        PRIVATE
        scene.cpp
        renderer3D.cpp
        volume_renderer.cpp

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../
        FILES
        scene.h
        renderer3D.h
        volume_renderer.h
        )
set_target_properties(Kasumi_Render3D PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_Render3D PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_Render3D_App main.cpp)
set_target_properties(Kasumi_Render3D_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render3D_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_Render3D_App PUBLIC Kasumi_Render3D)

# INSTALL TARGETS
INSTALL(
        TARGETS Kasumi_Render3D
        CONFIGURATIONS Release
        FILE_SET HEADERS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)