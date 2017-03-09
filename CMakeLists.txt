cmake_minimum_required(VERSION 3.7)
project(chip8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3 -ffast-math")

set(SOURCE_FILES
        src/main.cpp
        src/chip8/Cpu.cpp src/chip8/Cpu.hpp
        src/chip8/Memory.cpp src/chip8/Memory.hpp
        src/chip8/Constants.hpp
        src/Chip8.cpp src/Chip8.hpp)
add_executable(chip8 ${SOURCE_FILES})

# loading SFML library
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(chip8 ${SFML_LIBRARIES})
endif()