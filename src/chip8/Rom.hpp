#ifndef CHIP8_ROM_HPP
#define CHIP8_ROM_HPP


#include <string>
#include <vector>

struct Rom
{
    std::vector<uint8_t> binaryData = {};

    explicit Rom(std::string filePath);
};


#endif //CHIP8_ROM_HPP
