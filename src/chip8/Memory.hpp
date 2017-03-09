#ifndef CHIP8_MEMORY_HPP
#define CHIP8_MEMORY_HPP


#include <cstdint>
#include <array>
#include <vector>
#include "Constants.hpp"

using namespace Constants;

struct Memory
{
    Memory();
    ~Memory() = default;

    void clearMemory();
    void initFontSet();
    void loadBinary(const std::vector<uint8_t> binary);
    const uint8_t fetchOpcode(const uint8_t pc);

private:
    std::array<uint8_t, NMEM> storage_;
};


#endif //CHIP8_MEMORY_HPP
