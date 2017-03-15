#include "Memory.hpp"

Memory::Memory()
{
    clearMemory();
    initFontSet();
}

void Memory::clearMemory()
{
    storage.fill(0);
}

void Memory::initFontSet()
{
    auto index = 0;
    for (auto && e : Constants::FONT_SET) {
        storage[index] = static_cast<uint8_t>(e);
        index ++;
    }
}

void Memory::loadBinary(const std::vector<uint8_t> binary)
{
    auto index = 0;
    for (auto && e : binary) {
        storage[index + 512] = e;
        index ++;
    }
}

const uint16_t Memory::fetchOpcode(const uint16_t pc)
{
    return storage[pc] << 8 | storage[pc + 1];
}
