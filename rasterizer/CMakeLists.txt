cmake_minimum_required(VERSION 3.16)
project(Kasumi_rasterizer VERSION 1.0.0 DESCRIPTION "Kasumi Rasterizer" LANGUAGES CXX)

if (NOT TARGET Kasumi_backend)
    return()
endif ()

file(GLOB_RECURSE RASTERIZER_FILES
        app.h app.cpp
        )

add_executable(Kasumi_rasterizer test/main.cpp ${RASTERIZER_FILES})
set_target_properties(Kasumi_rasterizer PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
target_include_directories(Kasumi_rasterizer PUBLIC ../backends ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_rasterizer PUBLIC Kasumi_backend)
target_compile_definitions(Kasumi_rasterizer PUBLIC -DTestDir="${CMAKE_CURRENT_SOURCE_DIR}/test/")
