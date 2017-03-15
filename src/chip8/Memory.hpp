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
    ~Memory() = default;

    void clearMemory();
    void initFontSet();
    void loadBinary(const std::vector<uint8_t> binary);
    const uint16_t fetchOpcode(const uint16_t pc);
};


#endif //CHIP8_MEMORY_HPP
