include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(chip8Tests
        cpu_tests.cpp)

target_link_libraries(chip8Tests gtest gtest_main)
target_link_libraries(chip8Tests chip8)