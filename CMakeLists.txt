# Minimum CMake version and project name
cmake_minimum_required(VERSION 3.15)
project(gb-emulator LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all .cpp files in the 'src' directory automatically
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define the executable target named "gb-emulator"
add_executable(gb-emulator ${SOURCES}  "src/mmu/ppu.cpp" "src/interrupt.cpp")

# Add the 'include' directory path
target_include_directories(gb-emulator PUBLIC "include")

# Add compiler flags for warnings and debug symbols
target_compile_options(gb-emulator PRIVATE -Wall -Wextra -g)