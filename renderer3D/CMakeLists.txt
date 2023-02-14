cmake_minimum_required(VERSION 3.18)
project(Kasumi_Render3D VERSION 2.0.0 DESCRIPTION "Kasumi Renderer 3D" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    add_subdirectory(../backends Kasumi_Backends)
endif ()

file(GLOB_RECURSE src
        app.h app.cpp
        )
add_library(Kasumi_Render3D ${src})
set_target_properties(Kasumi_Render3D PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_Render3D PUBLIC Kasumi_Backends)