#include "elf_file.h"

#include <fstream>
#include <vector>

#include "util/exception.hpp"

#define ELF_MAGIC_LEN 4

ELFFile::ELFFile(const std::filesystem::path &path)
    : m_path(path)
{
    verifyIsExistentELFFile(path);

    std::ifstream inELFStream = open();

    // Parse partitions
    m_identification = Partition::Identification(inELFStream);
    m_header = Partition::Header(inELFStream, m_identification.end(), m_identification.lsb());

    inELFStream.close();

    m_identification.print();
    m_header.print();
}

void ELFFile::verifyIsExistentELFFile(const std::filesystem::path &path)
{
    if (!std::filesystem::exists(path))
        throwException<std::runtime_error>("Provided path is invalid: %s\n", path);

    // Verify ELF Identification
    std::ifstream inELFStream = open();

    Byte elfIdentification[ELF_MAGIC_LEN]{0x7f, 'E', 'L', 'F'};
    auto initialBytesInFile = readByteArray(inELFStream, ELF_MAGIC_LEN, 0, std::ios::beg);

    for (size_t idx = 0; idx < ELF_MAGIC_LEN; ++idx)
        if (elfIdentification[idx] != initialBytesInFile[idx])
            throw std::runtime_error("Provided file is not an ELF file.");

    inELFStream.close();
}

std::ifstream ELFFile::open()
{
    std::ifstream inELFStream;

    inELFStream.open(m_path, std::ios::binary | std::ios::in);
    if (!inELFStream.is_open())
        throwException<std::runtime_error>("ELF File could not be loaded: %s\n", m_path);

    return inELFStream;
}