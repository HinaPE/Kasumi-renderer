cmake_minimum_required(VERSION 3.24)
project(Kasumi_ShaderPainter VERSION 2.0.0 DESCRIPTION "Kasumi Shader Painter" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    message(FATAL_ERROR "Kasumi_Backends is not found")
    return()
endif ()

add_library(Kasumi_ShaderPainter STATIC)
target_sources(Kasumi_ShaderPainter
        PRIVATE
        shader_painter.cpp

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../
        FILES
        shader_painter.h
        )
set_target_properties(Kasumi_ShaderPainter PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_ShaderPainter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_ShaderPainter PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_ShaderPainter_App main.cpp)
set_target_properties(Kasumi_ShaderPainter_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_ShaderPainter_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_ShaderPainter_App PUBLIC Kasumi_ShaderPainter)
target_compile_definitions(
        Kasumi_ShaderPainter_App
        PUBLIC
        PainterShaderDir="${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
)

# INSTALL TARGETS
INSTALL(
        TARGETS Kasumi_ShaderPainter
        CONFIGURATIONS Release
        FILE_SET HEADERS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)