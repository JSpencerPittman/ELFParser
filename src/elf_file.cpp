#include "elf_file.h"

#include <fstream>
#include <vector>

#include "util/exception.hpp"

#define ELF_IDENT_LEN 4

ELFFile::ELFFile(const std::filesystem::path& path)
    : m_path(path)
{
    verifyIsExistentELFFile(path);

    readElfHeader();
}

void ELFFile::verifyIsExistentELFFile(const std::filesystem::path& path) {
    if(!std::filesystem::exists(path)) 
        throwException<std::runtime_error>("Provided path is invalid: %s\n", path);

    // Verify ELF Identification
    std::ifstream inELFStream = open();

    char elfIdentification[ELF_IDENT_LEN]{0x7f, 'E', 'L', 'F'};
    char initialBytesInFile[ELF_IDENT_LEN];
    inELFStream.read(initialBytesInFile, ELF_IDENT_LEN);
    if(!inELFStream.good())
        throw std::runtime_error("Could not read file identification.");

    for(size_t idx = 0; idx < ELF_IDENT_LEN; ++idx)
        if(elfIdentification[idx] != initialBytesInFile[idx])
            throw std::runtime_error("Provided file is not an ELF file.");

    inELFStream.close();
}

#define STREAMSIZE 30

void ELFFile::readElfHeader() {
    std::ifstream inELFStream = open();

    auto charBuffer = std::make_unique<char[]>(STREAMSIZE);
    inELFStream.read(charBuffer.get(), STREAMSIZE);

    for(size_t idx = 0; idx < STREAMSIZE; ++idx) {
        printf("%2lu: %d\n", idx, (unsigned char)charBuffer[idx]);
    }

    inELFStream.close();
}

std::ifstream ELFFile::open() {
    std::ifstream inELFStream;

    inELFStream.open(m_path, std::ios::binary | std::ios::in);
    if(!inELFStream.is_open())
        throwException<std::runtime_error>("ELF File could not be loaded: %s\n", m_path);

    return std::move(inELFStream);
}