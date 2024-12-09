#include "elf_file.h"

#include <fstream>
#include <vector>

#include "util/exception.hpp"
#include "util/read_bin.h"

#define ELF_MAGIC_LEN 4

ELFFile::ELFFile(const std::filesystem::path &path)
    : m_path(path)
{
    verifyIsExistentELFFile(path);

    readElfHeader();

    std::ifstream inELFStream = open();

    // Parse partitions
    m_identification = Partition::Identification(inELFStream);

    inELFStream.close();

    printf("File Class: %d\n", m_identification.fileClass());
    printf("Data Encoding: %d\n", m_identification.dataEncoding());
    printf("File Version: %d\n", m_identification.fileVersion());
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

#define STREAMSIZE 30

void ELFFile::readElfHeader()
{
    std::ifstream inELFStream = open();

    std::unique_ptr<Byte[]> buffer = readByteArray(inELFStream, STREAMSIZE);

    for (size_t idx = 0; idx < STREAMSIZE; ++idx)
    {
        printf("%2lu: %d\n", idx, buffer.get()[idx]);
    }

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