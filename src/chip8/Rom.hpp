#ifndef CHIP8_ROM_HPP
#define CHIP8_ROM_HPP


#include <string>
#include <vector>

struct Rom
{
    std::vector<uint8_t> binaryData = {};

    Rom(const std::string filePath);
    ~Rom() = default;
};


#endif //CHIP8_ROM_HPP
