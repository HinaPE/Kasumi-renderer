cmake_minimum_required(VERSION 3.16)
project(Kasumi_pathtracer VERSION 1.0.0 DESCRIPTION "Kasumi Pathtracer" LANGUAGES CXX)

if (NOT TARGET Kasumi_backend)
    return()
endif ()

file(GLOB_RECURSE PATHTRACER_FILES
        app.h app.cpp
        )

add_executable(Kasumi_pathtracer main.cpp ${PATHTRACER_FILES})
set_target_properties(Kasumi_pathtracer PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
target_include_directories(Kasumi_pathtracer PUBLIC ../../backends .)
target_link_libraries(Kasumi_pathtracer PUBLIC Kasumi_backend)
target_compile_definitions(
        Kasumi_pathtracer
        PUBLIC
        -DShaderDir="${KASUMI_BACKEND_DIR}/assets/shader/glsl/pathtracer"
        -DSceneDir="${KASUMI_BACKEND_DIR}/assets/scene/"
        -DModelDir="${KASUMI_BACKEND_DIR}/assets/model/"
)
