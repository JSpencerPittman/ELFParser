#include "partition/section_header.h"

#include "util/binary.h"

using namespace Partition;

SectionHeaderEntry::SectionHeaderEntry()
    : PartitionAbstract(0, 0), m_name(0), m_type(0), m_flags(0),
      m_addr(0), m_offset(0), m_sectionBytes(0), m_link(0), m_info(0), m_addralign(0),
      m_entsize(0)
{
}

SectionHeaderEntry::SectionHeaderEntry(std::ifstream &inELFStream, size_t offset,
                                       size_t entryBytes, bool lsb)
    : PartitionAbstract(offset, entryBytes)
{
    m_name = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb, offset, std::ios::beg);
    m_type = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_flags = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
    m_addr = readAndReinterpretByteArray<Elf64_Addr>(inELFStream, lsb);
    m_offset = readAndReinterpretByteArray<Elf64_Off>(inELFStream, lsb);
    m_sectionBytes = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
    m_link = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_info = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_addralign = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
    m_entsize = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
}

void SectionHeaderEntry::print() const
{
    printf("| --- Section Header Entry --- |\n");
    printLocation();
    printf("Name: %u\n", m_name);
    printf("Type: %u\n", m_type);
    printf("Flags: %lu\n", m_flags);
    printf("Address: %lu\n", m_addr);
    printf("Offset: %lu\n", m_offset);
    printf("Bytes in Section: %lu\n", m_sectionBytes);
    printf("Link: %u\n", m_link);
    printf("Info: %u\n", m_info);
    printf("Address Align: %lu\n", m_addralign);
    printf("Entry Size: %lu\n", m_entsize);
}

SectionHeader::SectionHeader()
    : PartitionAbstract(0, 0), m_locSize(0), m_locEntryBytes(0), m_entries(nullptr)
{
}

SectionHeader::SectionHeader(std::ifstream &inELFStream, size_t offset,
                             size_t size, size_t entryBytes, bool lsb)
    : PartitionAbstract(offset, size * entryBytes), m_locSize(size), m_locEntryBytes(entryBytes),
      m_entries(std::make_unique<SectionHeaderEntry[]>(size))
{
    for (size_t entryIdx = 0; entryIdx < size; ++entryIdx)
        m_entries[entryIdx] = SectionHeaderEntry(inELFStream, offset + (entryIdx * entryBytes),
                                                 entryBytes, lsb);
}

void SectionHeader::print() const
{
    printf("| --- Section Header --- |\n");
    printLocation();
    printf("Location[Size]: %lu\n", m_locSize);
    printf("Location[Entry Bytes]: %lu\n", m_locEntryBytes);
}