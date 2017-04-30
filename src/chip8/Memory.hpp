#ifndef CHIP8_MEMORY_HPP
#define CHIP8_MEMORY_HPP


#include <cstdint>
#include <array>
#include <vector>
#include "Constants.hpp"

using namespace Constants;

struct Memory
{
    std::array<uint8_t, NMEM> storage;

    Memory();

    void clearMemory();
    void initFontSet();
    void loadBinary(std::vector<uint8_t> binary);
    const uint16_t fetchOpcode(uint16_t pc);
};


#endif //CHIP8_MEMORY_HPP
