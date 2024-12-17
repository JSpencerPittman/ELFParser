#include "elf_file.h"

#include <fstream>
#include <vector>

#include "util/exception.hpp"
#include "util/binary.h"
#include "partition/string_table.h"
#include "partition/symbol_table.h"

#define ELF_MAGIC_LEN 4

ELFFile::ELFFile(const std::filesystem::path &path)
    : m_path(path)
{
    verifyIsExistentELFFile(path);

    std::ifstream inELFStream = open();

    // Parse partitions
    m_header = Partition::Header(inELFStream);
    m_sectionHeader = Partition::SectionHeader(inELFStream, m_header.shoff(), m_header.shnum(),
                                               m_header.shentsize(), m_header.lsb());

    // Extract string & symbol tables
    for (size_t idx = 0; idx < m_sectionHeader.size(); ++idx)
    {
        const Partition::SectionHeaderEntry &entry = m_sectionHeader[idx];
        Elf64_Word type = entry.type();
        if (type == SHT_SYMTAB || type == SHT_DYNSYM)
            m_symbolTableMap[idx] = Partition::SymbolTable(inELFStream, entry.offset(),
                                                           entry.sectionBytes(), m_header.lsb(),
                                                           entry.link());
        else if (type == SHT_STRTAB)
            m_stringTableMap[idx] = Partition::StringTable(inELFStream, entry.offset(),
                                                           entry.sectionBytes());
    }

    inELFStream.close();
}

void ELFFile::verifyIsExistentELFFile(const std::filesystem::path &path) const
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

std::unique_ptr<Byte[]> ELFFile::read(size_t offset, size_t bytes)
    const
{
    std::ifstream inELFStream = open();
    return readByteArray(inELFStream, bytes, offset, std::ios_base::beg);
}

std::unique_ptr<Byte[]> ELFFile::readFromSection(size_t sectionIdx, size_t offset, size_t bytes)
    const
{
    printf("Reading from section of size: %lu\n", sectionHeaderEntry(sectionIdx).sectionBytes());
    std::ifstream inELFStream = open();
    size_t sectionOffset = sectionHeaderEntry(sectionIdx).offset();
    return read(sectionOffset + offset, bytes);
}

std::ifstream ELFFile::open() const
{
    std::ifstream inELFStream;

    inELFStream.open(m_path, std::ios::binary | std::ios::in);
    if (!inELFStream.is_open())
        throwException<std::runtime_error>("ELF File could not be loaded: %s\n", m_path);

    return inELFStream;
}