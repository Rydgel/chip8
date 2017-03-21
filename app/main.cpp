#include <iostream>
#include <Chip8.hpp>

int main(int argc, char **argv)
{
    // todo choose Rom from CLI
    Chip8 chip8;
    chip8.loadRomFromFile("roms/INVADERS");
    chip8.run();

    return 0;
}