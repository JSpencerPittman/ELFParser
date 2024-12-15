#include "elf_file.h"

#include <fstream>
#include <vector>

#include "util/exception.hpp"
#include "section/string_table.h"

#define ELF_MAGIC_LEN 4

ELFFile::ELFFile(const std::filesystem::path &path)
    : m_path(path)
{
    verifyIsExistentELFFile(path);

    std::ifstream inELFStream = open();

    // Parse partitions
    m_identification = Partition::Identification(inELFStream);
    m_header = Partition::Header(inELFStream, m_identification.end(), m_identification.lsb());
    m_sectionHeader = Partition::SectionHeader(inELFStream, m_header.shoff(), m_header.shnum(),
                                               m_header.shentsize(), m_identification.lsb());

    m_identification.print();
    m_header.print();
    m_sectionHeader.print();

    // Locate String Table
    size_t stringTableIdx = 0;
    for(size_t idx = 0; idx < m_sectionHeader.numEntries(); ++idx)
        if(m_sectionHeader[idx].type() == SHT_STRTAB)
            stringTableIdx = idx;

    // Load String Table
    Section::StringTable strtab(m_sectionHeader[stringTableIdx]);

    // Print Section Names
    for(size_t idx = 0; idx < m_sectionHeader.numEntries(); ++idx)
        printf("Section(%lu): %s\n", idx,
            strtab.read(inELFStream, m_sectionHeader[idx].name()).c_str());

    inELFStream.close();
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