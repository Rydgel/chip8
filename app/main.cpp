#include <iostream>
#include <Chip8.hpp>

int main(int argc, char **argv)
{
    std::string filePath;

    if (argc > 1) {
        filePath = argv[1];
    } else {
        filePath = "roms/UFO";
    }

    Chip8 chip8;
    chip8.loadRomFromFile(filePath);
    chip8.run();

    return 0;
}