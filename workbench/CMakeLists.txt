cmake_minimum_required(VERSION 3.16)
project(Kasumi_workbench VERSION 1.0.0 DESCRIPTION "Kasumi Workbench Renderer" LANGUAGES CXX)

if (NOT TARGET Kasumi_backend)
    return()
endif ()

file(GLOB_RECURSE WORKBENCH_FILES
        api.h
        app.h app.cpp
        scene/*h scene/*.cpp
        gui/*h gui/*.cpp
        )

add_executable(Kasumi_workbench main.cpp ${WORKBENCH_FILES})
set_target_properties(Kasumi_workbench PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
target_include_directories(Kasumi_workbench PUBLIC ../backends ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_workbench PUBLIC Kasumi_backend)
target_compile_definitions(
        Kasumi_workbench
        PUBLIC
        -DShaderDir="${KASUMI_BACKEND_DIR}/assets/shader/glsl/"
        -DSceneDir="${KASUMI_BACKEND_DIR}/assets/scene/"
        -DModelDir="${KASUMI_BACKEND_DIR}/assets/model/"
)
