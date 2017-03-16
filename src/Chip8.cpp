#include <chip8/Rom.hpp>
#include <thread>
#include <iostream>
#include "Chip8.hpp"

void Chip8::loadRomFromFile(const std::string filePath)
{
    Rom rom(filePath);
    memory_.loadBinary(rom.binaryData);
}

void Chip8::run()
{
    using namespace std::chrono_literals;
    while (true) {
        cpu_.emulateCycle();
        // std::this_thread::sleep_for(10ms);
        if (cpu_.drawFlag) {
            std::cout << cpu_ << std::endl;
            cpu_.drawFlag = false;
        }

    }
}
