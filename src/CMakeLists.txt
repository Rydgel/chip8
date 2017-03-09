project(chip8)

set(HEADER_FILES
        chip8/Cpu.hpp
        chip8/Memory.hpp
        chip8/Constants.hpp
        Chip8.hpp)

set(SOURCE_FILES
        chip8/Cpu.cpp
        chip8/Memory.cpp
        Chip8.cpp)

add_library(chip8 STATIC ${SOURCE_FILES} ${HEADER_FILES})

# loading SFML library
find_package(SFML REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(chip8 ${SFML_LIBRARIES})
endif()