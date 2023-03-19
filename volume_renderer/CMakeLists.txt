cmake_minimum_required(VERSION 3.24)
project(Kasumi_VolumeRenderer VERSION 2.0.0 DESCRIPTION "Kasumi Shader Painter" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    message(FATAL_ERROR "Kasumi_Backends is not found")
    return()
endif ()

add_library(Kasumi_VolumeRenderer STATIC)
target_sources(Kasumi_VolumeRenderer
        PRIVATE
        volume_renderer.cpp

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../
        FILES
        volume_renderer.h
        )
set_target_properties(Kasumi_VolumeRenderer PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_VolumeRenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_VolumeRenderer PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_VolumeRenderer_App main.cpp)
set_target_properties(Kasumi_VolumeRenderer_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_VolumeRenderer_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_VolumeRenderer_App PUBLIC Kasumi_VolumeRenderer)

# INSTALL TARGETS
INSTALL(
        TARGETS Kasumi_VolumeRenderer
        CONFIGURATIONS Release
        FILE_SET HEADERS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)