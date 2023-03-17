cmake_minimum_required(VERSION 3.24)
project(Kasumi_Render2D VERSION 2.0.0 DESCRIPTION "Kasumi Renderer 2D" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    message(FATAL_ERROR "Kasumi_Backends is not found")
    return()
endif ()

add_library(Kasumi_Render2D STATIC)
file(GLOB headers renderer2D.h scene.h objects/*.h)
file(GLOB sources renderer2D.cpp scene.cpp objects/*.cpp)
target_sources(Kasumi_Render2D
        PRIVATE
        ${sources}

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../
        FILES
        ${headers}
        )
set_target_properties(Kasumi_Render2D PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render2D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_Render2D PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_Render2D_App main.cpp)
set_target_properties(Kasumi_Render2D_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_Render2D_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_Render2D_App PUBLIC Kasumi_Render2D)