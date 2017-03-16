#include <iostream>
#include <Chip8.hpp>

int main()
{
    Chip8 chip8;
    chip8.loadRomFromFile("roms/INVADERS");
    chip8.run();

    return 0;
}