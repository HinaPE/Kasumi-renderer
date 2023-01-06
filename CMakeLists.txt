cmake_minimum_required(VERSION 3.18)
project(Kasumi VERSION 0.3.0 DESCRIPTION "Kasumi: Illumine the Endless Night." LANGUAGES CXX)

if (NOT TARGET Kasumi_backend)
    set(KASUMI_BACKEND_DIR "${CMAKE_CURRENT_SOURCE_DIR}/backends" CACHE PATH "Path to Kasumi backend")
    add_subdirectory(${KASUMI_BACKEND_DIR} Kasumi_backend)
endif ()

add_subdirectory(renderer)
add_subdirectory(tiny2d-renderer)