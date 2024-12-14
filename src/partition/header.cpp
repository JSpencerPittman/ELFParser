#include "partition/header.h"

#include "util/binary.h"

using namespace Partition;

Header::Header()
    : m_offset(0), m_type(0), m_machine(0), m_version(0), m_entry(0), m_phoff(0), m_shoff(0), m_flags(0), m_ehsize(0), m_phentsize(0), m_phnum(0), m_shentsize(0), m_shnum(0), m_shstrndx(0)
{
}

Header::Header(std::ifstream &inELFStream, size_t beginIdx, bool lsb)
    : m_offset(beginIdx)
{
    m_type = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb, m_offset, std::ios::beg);
    m_machine = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
    m_version = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_entry = readAndReinterpretByteArray<Elf64_Addr>(inELFStream, lsb);
    m_phoff = readAndReinterpretByteArray<Elf64_Off>(inELFStream, lsb);
    m_shoff = readAndReinterpretByteArray<Elf64_Off>(inELFStream, lsb);
    m_flags = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb);
    m_ehsize = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
    m_phentsize = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
    m_phnum = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
    m_shentsize = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
    m_shnum = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
    m_shstrndx = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
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