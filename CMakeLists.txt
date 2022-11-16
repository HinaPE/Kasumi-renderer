cmake_minimum_required(VERSION 3.16)
project(Kasumi VERSION 1.1.2 DESCRIPTION "Kasumi: Illumine the Endless Night." LANGUAGES CXX)

if (NOT TARGET Kasumi_backend)
    add_subdirectory(universal_graphics Kasumi_backend)
endif ()
add_subdirectory(workbench)

#file(GLOB_RECURSE KASUMI_GRAPHICS_API "universal_graphics/*.cpp" "universal_graphics/*.h")
#file(GLOB_RECURSE KASUMI_WORKBENCH "workbench/*.cpp" "workbench/*.h")
#file(GLOB_RECURSE KASUMI_RASTERIZER "rasterizer/*.cpp" "rasterizer/*.h")
#file(GLOB_RECURSE KASUMI_PATHTRACER "pathtracer/*.cpp" "pathtracer/*.h")
#
#set(KASUMI_Imgui_OpenGL
#        "deps/imgui/imgui.h"
#        "deps/imgui/imgui.cpp"
#        "deps/imgui/imgui_draw.cpp"
#        "deps/imgui/imgui_widgets.cpp"
#        "deps/imgui/imgui_tables.cpp"
#        "deps/imgui/imconfig.h"
#        "deps/imgui/imgui_internal.h"
#        "deps/imgui/imstb_rectpack.h"
#        "deps/imgui/imstb_textedit.h"
#        "deps/imgui/imstb_truetype.h"
#        "deps/imgui/backends/imgui_impl_opengl3.cpp"
#        "deps/imgui/backends/imgui_impl_opengl3.h"
#        "deps/imgui/backends/imgui_impl_glfw.cpp"
#        "deps/imgui/backends/imgui_impl_glfw.h"
#        )
#
#set(KASUMI_SRC
#        ${KASUMI_GRAPHICS_API}
#        ${KASUMI_WORKBENCH}
#        ${KASUMI_RASTERIZER}
#        ${KASUMI_PATHTRACER}
#        ${KASUMI_Imgui_OpenGL}
#        )
#
#add_library(Kasumi_Renderer ${KASUMI_SRC} math_api.h)
#set_target_properties(Kasumi_Renderer PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)
#target_include_directories(Kasumi_Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${KASUMI_COMMON_DIR})
#target_link_libraries(Kasumi_Renderer PUBLIC HinaPE_Common)
#target_compile_definitions(
#        Kasumi_Renderer
#        PUBLIC
#        KASUMI_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/builtin_shaders/"
#        KASUMI_MODEL_DIR="${CMAKE_CURRENT_SOURCE_DIR}/builtin_models/"
#)
#
## setup OS-specific options
#if (APPLE)
#    set(CMAKE_EXE_LINKER_FLAGS "-framework AppKit")
#endif ()
#if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#    target_compile_options(Kasumi_Renderer PUBLIC -fno-omit-frame-pointer)
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
#    set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
#endif ()
#
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(Kasumi_Renderer PUBLIC Threads::Threads) # std::thread need pthread lib to be linked

