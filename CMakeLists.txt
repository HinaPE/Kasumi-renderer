cmake_minimum_required(VERSION 3.16)
project(Kasumi VERSION 1.1.2 DESCRIPTION "Kasumi: Illumine the Endless Night." LANGUAGES CXX)

set(KASUMI_COMMON_DIR "./common")

if (NOT TARGET HinaPE_Common)
    add_subdirectory(${KASUMI_COMMON_DIR} HinaPE_Common)
endif ()

file(GLOB_RECURSE KASUMI_GRAPHICS_API "graphics_api/*.cpp" "graphics_api/*.h")
file(GLOB_RECURSE KASUMI_WORKBENCH "workbench/*.cpp" "workbench/*.h")
file(GLOB_RECURSE KASUMI_RASTERIZER "rasterizer/*.cpp" "rasterizer/*.h")
file(GLOB_RECURSE KASUMI_PATHTRACER "pathtracer/*.cpp" "pathtracer/*.h")

set(KASUMI_OpenGL
        "deps/imgui/imgui_impl_opengl3.cpp"
        "deps/imgui/imgui_impl_opengl3.h"
        "deps/imgui/imgui_impl_glfw.cpp"
        "deps/imgui/imgui_impl_glfw.h"
        )

set(KASUMI_SRC
        ${KASUMI_GRAPHICS_API}
        ${KASUMI_WORKBENCH}
        ${KASUMI_RASTERIZER}
        ${KASUMI_PATHTRACER}
        ${KASUMI_OpenGL}
        )

add_library(Kasumi_Renderer ${KASUMI_SRC} math_api.h)
set_target_properties(Kasumi_Renderer PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
target_include_directories(Kasumi_Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_Renderer PUBLIC HinaPE_Common)
target_compile_definitions(
        Kasumi_Renderer
        PUBLIC
        KASUMI_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/builtin_shaders/"
        KASUMI_MODEL_DIR="${CMAKE_CURRENT_SOURCE_DIR}/builtin_models/"
)
# setup OS-specific options
if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-framework AppKit")
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(Kasumi_Renderer PUBLIC -fno-omit-frame-pointer)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
endif ()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Kasumi_Renderer PUBLIC Threads::Threads) # std::thread need pthread lib to be linked
if (NOT TARGET SDL2)
    add_subdirectory("deps/SDL" "${CMAKE_CURRENT_BINARY_DIR}/SDL")
endif ()
if (NOT TARGET imgui)
    add_subdirectory("deps/imgui/" "${CMAKE_CURRENT_BINARY_DIR}/imgui")
    target_include_directories(imgui PUBLIC ../render-engine/ ./common)
endif ()
if (NOT TARGET glad)
    add_subdirectory("deps/glad/" "${CMAKE_CURRENT_BINARY_DIR}/glad")
    target_include_directories(glad PUBLIC deps)
endif ()
if (NOT TARGET nfd)
    add_subdirectory("deps/nfd/" "${CMAKE_CURRENT_BINARY_DIR}/nfd")
endif ()
if (NOT TARGET sf_libs)
    add_subdirectory("deps/sf_libs/" "${CMAKE_CURRENT_BINARY_DIR}/sf_libs")
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
    add_subdirectory("deps/assimp/" "${CMAKE_CURRENT_BINARY_DIR}/assimp")
    if (APPLE)
        target_compile_options(assimp PUBLIC -Wno-error)
    endif ()
endif ()
if (NOT TARGET glfw)
    add_subdirectory("deps/glfw3" "${CMAKE_CURRENT_BINARY_DIR}/glfw3")
endif ()
target_include_directories(Kasumi_Renderer PUBLIC ${ASSIMP_INCLUDE_DIRS})

# define include paths
target_include_directories(Kasumi_Renderer PUBLIC "deps" "deps/assimp/include" "deps/SDL/include" "deps/glfw3/include")
target_include_directories(Kasumi_Renderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Kasumi_Renderer PUBLIC "${KASUMI_COMMON_DIR}")


# link libraries
if (WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    target_link_libraries(Kasumi_Renderer PUBLIC Winmm)
    target_link_libraries(Kasumi_Renderer PUBLIC Version)
    target_link_libraries(Kasumi_Renderer PUBLIC Setupapi)
    target_link_libraries(Kasumi_Renderer PUBLIC Shcore)
endif ()
target_link_libraries(Kasumi_Renderer PUBLIC SDL2::SDL2-static)
target_link_libraries(Kasumi_Renderer PUBLIC SDL2::SDL2main)
target_link_libraries(Kasumi_Renderer PUBLIC assimp)
target_link_libraries(Kasumi_Renderer PUBLIC nfd)
target_link_libraries(Kasumi_Renderer PUBLIC sf_libs)
target_link_libraries(Kasumi_Renderer PUBLIC imgui)
target_link_libraries(Kasumi_Renderer PUBLIC glad)
target_link_libraries(Kasumi_Renderer PUBLIC glfw)

add_executable(test test/main.cpp)
set_target_properties(test PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
target_link_libraries(test PUBLIC Kasumi_Renderer)
