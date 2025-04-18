cmake_minimum_required(VERSION 3.15)
project(Chess)

# Set C++ standard (C++20 or C++23 depending on compiler)
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# MSVC-specific compile options
if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

# Define source and header directories
include_directories(include)

# List all source files
set(SOURCES
    src/main.cpp
    src/Chess.cpp
    src/GameEngine.cpp
    src/Rook.cpp
)

# Create the executable
add_executable(Chess ${SOURCES})
