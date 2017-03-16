#include <ios>
#include <fstream>
#include "Rom.hpp"

Rom::Rom(const std::string filePath)
{
    try {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        file.unsetf(std::ios::skipws);
        std::streampos fileSize;
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // reserve capacity
        binaryData.reserve(static_cast<unsigned long>(fileSize));

        // read the data:
        binaryData.insert(binaryData.begin(),
                          std::istream_iterator<uint8_t>(file),
                          std::istream_iterator<uint8_t>());
    } catch (...) {
        throw std::runtime_error("Can't find the rom filepath\n");
    }
}
