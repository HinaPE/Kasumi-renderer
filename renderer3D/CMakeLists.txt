cmake_minimum_required(VERSION 3.23)
project(Kasumi_Render3D VERSION 2.0.0 DESCRIPTION "Kasumi Renderer 3D" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    add_subdirectory(../backends Kasumi_Backends)
endif ()

file(GLOB_RECURSE src
        scene.cpp scene.h
        renderer3D.cpp renderer3D.h
        )
add_library(Kasumi_Render3D ${src})
set_target_properties(Kasumi_Render3D PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_Render3D PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_Render3D_App main.cpp)
set_target_properties(Kasumi_Render3D_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render3D_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_Render3D_App PUBLIC Kasumi_Render3D)

# INSTALL TARGETS
set_target_properties(Kasumi_Render3D PROPERTIES PUBLIC_HEADER
        "renderer3D.h;scene.h"
        )
INSTALL(
        TARGETS Kasumi_Render3D
        CONFIGURATIONS Release
        PUBLIC_HEADER DESTINATION include/renderer3D
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)