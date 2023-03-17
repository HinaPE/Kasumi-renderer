cmake_minimum_required(VERSION 3.24)
project(Kasumi_FunctionViewer VERSION 2.0.0 DESCRIPTION "Kasumi Function Viewer" LANGUAGES CXX)

if (NOT TARGET Kasumi_Backends)
    message(FATAL_ERROR "Kasumi_Backends is not found")
    return()
endif ()

add_library(Kasumi_FunctionViewer STATIC)
target_sources(Kasumi_FunctionViewer
        PRIVATE
        function_viewer2D.cpp

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../
        FILES
        function_viewer2D.h
        )
set_target_properties(Kasumi_FunctionViewer PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_FunctionViewer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kasumi_FunctionViewer PUBLIC Kasumi_Backends)

# APP EXECUTABLE
add_executable(Kasumi_FunctionViewer_App main.cpp)
set_target_properties(Kasumi_FunctionViewer_App PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(Kasumi_FunctionViewer_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(Kasumi_FunctionViewer_App PUBLIC Kasumi_FunctionViewer)

# INSTALL TARGETS
INSTALL(
        TARGETS Kasumi_FunctionViewer
        CONFIGURATIONS Release
        FILE_SET HEADERS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)