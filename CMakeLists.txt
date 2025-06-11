cmake_minimum_required(VERSION 3.16)
project(SimPhy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all>=2.5)

# Include directories
include_directories(include)

# Simple Harmonic Oscillator executable
add_executable(simple_harmonic_oscillator
    src/simple_harmonic_oscillator/main.cpp
)

target_link_libraries(simple_harmonic_oscillator 
    ${SFML_LIBRARIES}
)

target_include_directories(simple_harmonic_oscillator PRIVATE ${SFML_INCLUDE_DIRS})
target_compile_options(simple_harmonic_oscillator PRIVATE ${SFML_CFLAGS_OTHER})
