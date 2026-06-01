cmake_minimum_required(VERSION 3.21)

project(QuadLib LANGUAGES CXX)

include(FetchContent)

# SDL3

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_CAMERA OFF CACHE BOOL "" FORCE)
set(SDL_RENDER OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI OFF CACHE BOOL "" FORCE)
set(SDL_POWER OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
set(SDL_DIALOG OFF CACHE BOOL "" FORCE)

if(NOT TARGET SDL3::SDL3)

    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.14
    )

    FetchContent_MakeAvailable(SDL3)

endif()

# bgfx

# Put all executables in build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
option(QUADLIB_BGFX_TOOLS "Enable BGFX shader tools" ON)
option(QUADLIB_CORE "Access all core functions throught api" ON)

set(BGFX_BUILD_TOOLS ${QUADLIB_BGFX_TOOLS} CACHE BOOL "" FORCE)

if(NOT TARGET bgfx)

    FetchContent_Declare(
        bgfx
        GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
        GIT_TAG master
    )

    FetchContent_MakeAvailable(bgfx)

endif()

# Your library

add_library(QuadLib
    src/api/quadlib.cpp
    src/core/core.cpp
    src/core/shader.cpp
    src/core/mesh.cpp
    src/core/texture.cpp
)


target_compile_definitions(QuadLib PUBLIC
    QUADLIB_PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
    QUADLIB_SHADERC="$<TARGET_FILE:shaderc>"
    QUADLIB_BGFX_SRC_DIR="${bgfx_SOURCE_DIR}/bgfx/src"
)

if(QUADLIB_BGFX_TOOLS)
    target_compile_definitions(QuadLib PUBLIC QUADLIB_BGFX_TOOLS)
endif()

if(QUADLIB_CORE)
    target_compile_definitions(QuadLib PUBLIC QUADLIB_CORE)
endif()

target_include_directories(QuadLib PUBLIC
    include
)

target_link_libraries(QuadLib PUBLIC
    SDL3::SDL3 
    bgfx
    bx
    bimg
)

target_compile_features(QuadLib PUBLIC cxx_std_20)

# test app

add_executable(QuadLibExample
    src/main.cpp
)

target_link_libraries(QuadLibExample
PRIVATE
    QuadLib
)