cmake_minimum_required(VERSION 3.16)
project(Kasumi VERSION 1.1.2 DESCRIPTION "Kasumi: Illumine the Endless Night." LANGUAGES CXX)

if (NOT TARGET Kasumi_backend)
    add_subdirectory(backends Kasumi_backend)
endif ()
add_subdirectory(workbench)
add_subdirectory(rasterizer)
add_subdirectory(pathtracer)
