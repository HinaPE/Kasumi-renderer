cmake_minimum_required(VERSION 3.16)
project(Kasumi_backend VERSION 1.0.0 DESCRIPTION "Multi-backend Graphics Api" LANGUAGES CXX)

option(OpenGL "Enable OpenGL backend" ON)
option(Vulkan "Enable Vulkan backend" OFF)

if (NOT TARGET HinaPE_Common)
    set(KASUMI_COMMON_DIR "../common")
    add_subdirectory(${KASUMI_COMMON_DIR} HinaPE_Common)
endif ()

file(GLOB UNIVERSE_FILES
        platform.h
        shader.h
        mesh.h
        texture.h
        model.h
        framebuffer.h
        )

if (OpenGL)
    file(GLOB OPENGL_IMPL
            backends/OpenGL/shader.cpp
            backends/OpenGL/platform.cpp
            backends/OpenGL/mesh.cpp
            backends/OpenGL/texture.cpp
            backends/OpenGL/framebuffer.cpp
            backends/OpenGL/model.cpp
            )
    if (NOT TARGET glad)
        add_subdirectory(deps/glad)
        target_include_directories(glad PUBLIC deps)
    endif ()
    if (NOT TARGET glfw)
        add_subdirectory(deps/glfw3)
    endif ()
    if (NOT TARGET assimp)
        set(ASSIMP_BUILD_COLLADA_IMPORTER TRUE)
        set(ASSIMP_BUILD_OBJ_IMPORTER TRUE)
        set(ASSIMP_BUILD_PLY_IMPORTER TRUE)
        set(ASSIMP_BUILD_FBX_IMPORTER TRUE)
        set(ASSIMP_BUILD_GLTF_IMPORTER TRUE)
        set(ASSIMP_BUILD_3DS_IMPORTER TRUE)
        set(ASSIMP_BUILD_STL_IMPORTER TRUE)
        set(ASSIMP_BUILD_BLEND_IMPORTER TRUE)
        set(ASSIMP_BUILD_COLLADA_EXPORTER TRUE)
        add_subdirectory(deps/assimp)
        if (APPLE)
            target_compile_options(assimp PUBLIC -Wno-error)
        endif ()
    endif ()
    add_library(Kasumi_backend ${UNIVERSE_FILES} ${OPENGL_IMPL})
    set_target_properties(Kasumi_backend PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
    target_include_directories(Kasumi_backend PUBLIC ${KASUMI_COMMON_DIR} deps deps/assimp/include deps/glfw3/include deps/imgui deps/stb)
    target_link_libraries(Kasumi_backend PUBLIC assimp)
    target_link_libraries(Kasumi_backend PUBLIC glad)
    target_link_libraries(Kasumi_backend PUBLIC glfw)
    target_link_libraries(Kasumi_backend PUBLIC HinaPE_Common)
endif ()

add_executable(test test/main.cpp)
set_target_properties(test PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
target_link_libraries(test PUBLIC Kasumi_backend)