project(chip8)

set(HEADER_FILES
        chip8/Cpu.hpp
        chip8/Memory.hpp
        chip8/Constants.hpp
        Chip8.hpp
        chip8/Rom.hpp
        graphics/Window.hpp
        graphics/opengl/OpenGLError.hpp
        graphics/Timer.hpp
        audio/Sound.hpp
        graphics/opengl/Shader.hpp
        graphics/opengl/Vertex.hpp)

set(SOURCE_FILES
        chip8/Cpu.cpp
        chip8/Memory.cpp
        Chip8.cpp
        chip8/Rom.cpp
        graphics/Window.cpp
        graphics/opengl/OpenGLError.cpp
        graphics/Timer.cpp
        audio/Sound.cpp
        graphics/opengl/Shader.cpp)

add_library(chip8 STATIC ${SOURCE_FILES} ${HEADER_FILES})

# loading fmt library
add_subdirectory(lib/fmt-3.0.1)
target_link_libraries(chip8 fmt)

# loading glad
add_subdirectory(lib/glad)
target_link_libraries(chip8 glad)
include_directories(lib/glad)

# loading glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw-3.2.1)
target_link_libraries(chip8 glfw)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(chip8 ${OPENGL_gl_LIBRARY})
endif()

# loading glm
include_directories(lib/glm-0.9.8.4)

# loading OpenAL
find_package(OpenAL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENAL_INCLUDE_DIR})
    target_link_libraries(chip8 ${OPENAL_LIBRARY})
endif()