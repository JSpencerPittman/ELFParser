#include "partition/section_header.h"

#include "util/binary.h"

using namespace Partition;

SectionHeaderEntry::SectionHeaderEntry()
    : m_locOffset(0), m_locEntrySize(0), m_name(0), m_type(0), m_flags(0),
      m_addr(0), m_offset(0), m_size(0), m_link(0), m_info(0), m_addralign(0),
      m_entsize(0)
{
}

SectionHeaderEntry::SectionHeaderEntry(std::ifstream &inELFStream, size_t offset,
                                       size_t entrySize, bool lsb)
    : m_locOffset(offset), m_locEntrySize(entrySize)
{
    m_name = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb, offset, std::ios::beg);
    m_type = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_flags = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
    m_addr = readAndReinterpretByteArray<Elf64_Addr>(inELFStream, lsb);
    m_offset = readAndReinterpretByteArray<Elf64_Off>(inELFStream, lsb);
    m_size = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
    m_link = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_info = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_addralign = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
    m_entsize = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
}

void SectionHeaderEntry::print() const
{
    printf("| --- Section Header Entry --- |\n");
    printf("Location[Offset]: %lu\n", m_locOffset);
    printf("Location[Entry Size]: %lu\n", m_locEntrySize);
    printf("Name: %u\n", m_name);
    printf("Type: %u\n", m_type);
    printf("Flags: %lu\n", m_flags);
    printf("Address: %lu\n", m_addr);
    printf("Offset: %lu\n", m_offset);
    printf("Size: %lu\n", m_size);
    printf("Link: %u\n", m_link);
    printf("Info: %u\n", m_info);
    printf("Address Align: %lu\n", m_addralign);
    printf("Entry Size: %lu\n", m_entsize);
}

SectionHeader::SectionHeader()
    : m_locOffset(0), m_locNumEntries(0), m_locEntrySize(0), m_entries(nullptr)
{
}

SectionHeader::SectionHeader(std::ifstream &inELFStream, size_t offset,
                             size_t numEntries, size_t entrySize, bool lsb)
    : m_locOffset(offset), m_locNumEntries(numEntries), m_locEntrySize(entrySize),
      m_entries(std::make_unique<SectionHeaderEntry[]>(numEntries))
{
    for (size_t entryIdx = 0; entryIdx < numEntries; ++entryIdx)
        m_entries[entryIdx] = SectionHeaderEntry(inELFStream, offset + (entryIdx * entrySize),
                                                 entrySize, lsb);
}

void SectionHeader::print() const
{
    printf("| --- Section Header --- |\n");
    printf("Location[Offset]: %lu\n", m_locOffset);
    printf("Location[Num Entries]: %lu\n", m_locNumEntries);
    printf("Location[Entry Size]: %lu\n", m_locEntrySize);
}