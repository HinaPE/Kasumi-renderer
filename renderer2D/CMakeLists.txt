cmake_minimum_required(VERSION 3.23)
project(Kasumi_Render2D VERSION 2.0.0 DESCRIPTION "Kasumi Renderer 2D" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    add_subdirectory(../backends Kasumi_Backends)
endif ()

file(GLOB_RECURSE src
        objects/*.h objects/*.cpp
        scene.h scene.cpp
        )
add_library(Kasumi_Render2D ${src})
set_target_properties(Kasumi_Render2D PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render2D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_Render2D PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_Render2D_App main.cpp)
set_target_properties(Kasumi_Render2D_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render2D_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_Render2D_App PUBLIC Kasumi_Render2D)