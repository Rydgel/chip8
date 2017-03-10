cmake_minimum_required(VERSION 3.7)
project(chip8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3 -ffast-math")

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)

set(SOURCE_FILES app/main.cpp)
add_executable(chip8_run ${SOURCE_FILES})
target_link_libraries(chip8_run chip8)

file(COPY roms DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}.)