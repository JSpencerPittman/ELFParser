#include "partition/header.h"

#include "util/binary.h"

using namespace Partition;

Header::Header()
    : m_beginIdx(0), m_type(0), m_machine(0), m_version(0), m_entry(0), m_phoff(0), m_shoff(0), m_flags(0), m_ehsize(0), m_phentsize(0), m_phnum(0), m_shentsize(0), m_shnum(0), m_shstrndx(0)
{
}

Header::Header(std::ifstream &inELFStream, size_t beginIdx, bool lsb)
    : m_beginIdx(beginIdx)
{
    auto type = readByteArray(inELFStream, 2, beginIdx, std::ios::beg);
    m_type = reinterpretBytes<Elf64_Half>(type.get(), 2, lsb);

    auto machine = readByteArray(inELFStream, 2);
    m_machine = reinterpretBytes<Elf64_Half>(machine.get(), 2, lsb);

    auto version = readByteArray(inELFStream, 4);
    m_version = reinterpretBytes<Elf64_Word>(version.get(), 4, lsb);

    auto entry = readByteArray(inELFStream, 8);
    m_entry = reinterpretBytes<Elf64_Addr>(entry.get(), 8, lsb);

    auto phoff = readByteArray(inELFStream, 8);
    m_phoff = reinterpretBytes<Elf64_Off>(phoff.get(), 8, lsb);

    auto shoff = readByteArray(inELFStream, 8);
    m_shoff = reinterpretBytes<Elf64_Off>(shoff.get(), 8, lsb);

    auto flags = readByteArray(inELFStream, 4);
    m_flags = reinterpretBytes<Elf64_Word>(flags.get(), 4, lsb);

    auto ehsize = readByteArray(inELFStream, 2);
    m_ehsize = reinterpretBytes<Elf64_Half>(ehsize.get(), 2, lsb);

    auto phentsize = readByteArray(inELFStream, 2);
    m_phentsize = reinterpretBytes<Elf64_Half>(phentsize.get(), 2, lsb);

    auto phnum = readByteArray(inELFStream, 2);
    m_phnum = reinterpretBytes<Elf64_Half>(phnum.get(), 2, lsb);

    auto shentsize = readByteArray(inELFStream, 2);
    m_shentsize = reinterpretBytes<Elf64_Half>(shentsize.get(), 2, lsb);

    auto shnum = readByteArray(inELFStream, 2);
    m_shnum = reinterpretBytes<Elf64_Half>(shnum.get(), 2, lsb);

    auto shstrndx = readByteArray(inELFStream, 2);
    m_shstrndx = reinterpretBytes<Elf64_Half>(shstrndx.get(), 2, lsb);
}

void Header::print() const
{
    printf("Type: %u\n", m_type);
    printf("Machine: %u\n", m_machine);
    printf("Version: %u\n", m_version);
    printf("Entry: %lu\n", m_entry);
    printf("Program Header Offset: %lu\n", m_phoff);
    printf("Section Header Offset: %lu\n", m_shoff);
    printf("Flags: %u\n", m_flags);
    printf("ELF Header Size: %u\n", m_ehsize);
    printf("Program Header Entry Size: %u\n", m_phentsize);
    printf("Num Entries in Program Header: %u\n", m_phnum);
    printf("Section Header Entry Size: %u\n", m_shentsize);
    printf("Num Entries in Section Header: %u\n", m_shnum);
    printf("Section Header Table Index: %u\n", m_shstrndx);
}