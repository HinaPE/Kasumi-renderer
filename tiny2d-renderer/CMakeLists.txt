cmake_minimum_required(VERSION 3.16)
project(Kasumi-2d-renderer VERSION 1.0.0 DESCRIPTION "Kasumi Workbench 2D Renderer" LANGUAGES CXX)

if (NOT TARGET Kasumi_backend)
    return()
endif ()

file(GLOB_RECURSE WORKBENCH_FILES
        app.h app.cpp shape.h
        )

add_library(tiny_2D_renderer ${WORKBENCH_FILES})
set_target_properties(tiny_2D_renderer PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
target_include_directories(tiny_2D_renderer PUBLIC ${KASUMI_BACKEND_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_include_directories(tiny_2D_renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tiny_2D_renderer PUBLIC Kasumi_backend)