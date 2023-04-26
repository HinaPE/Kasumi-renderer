cmake_minimum_required(VERSION 3.24)
project(Kasumi_DeferredRender3D VERSION 2.0.0 DESCRIPTION "Kasumi Deferred Renderer 3D" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    message(FATAL_ERROR "Kasumi_Backends is not found")
    return()
endif ()

add_library(Kasumi_DeferredRender3D STATIC)
target_sources(Kasumi_DeferredRender3D
        PRIVATE
        deferred_renderer3D.cpp

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../
        FILES
        deferred_renderer3D.h
        )
set_target_properties(Kasumi_DeferredRender3D PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_DeferredRender3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_DeferredRender3D PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_DeferredRender3D_App main.cpp)
set_target_properties(Kasumi_DeferredRender3D_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_DeferredRender3D_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_DeferredRender3D_App PUBLIC Kasumi_DeferredRender3D)

# INSTALL TARGETS
INSTALL(
        TARGETS Kasumi_DeferredRender3D
        CONFIGURATIONS Release
        FILE_SET HEADERS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)