#include "partition/symbol_table.h"

#include "util/binary.h"

using namespace Partition;

SymbolTableEntry::SymbolTableEntry()
    : PartitionAbstract(0, 0), m_name(0), m_info(0), m_other(0), m_shndx(0), m_value(0), m_size(0)
{
}

SymbolTableEntry::SymbolTableEntry(std::ifstream &inELFStream, size_t offset, bool lsb)
    : PartitionAbstract(offset, PARTITION_SYMTAB_ENTRY_SIZE)
{
    m_name = readAndReinterpretByteArray<Elf64_Word>(inELFStream, lsb, offset, std::ios::beg);
    m_info = readAndReinterpretByteArray<Byte>(inELFStream, lsb);
    m_other = readAndReinterpretByteArray<Byte>(inELFStream, lsb);
    m_shndx = readAndReinterpretByteArray<Elf64_Half>(inELFStream, lsb);
    m_value = readAndReinterpretByteArray<Elf64_Addr>(inELFStream, lsb);
    m_size = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
}

void SymbolTableEntry::print() const
{
    printf("| --- Symbol Table Entry --- |\n");
    printf("Location[Offset]: %lu\n", m_locOffset);
    printf("Name: %u\n", m_name);
    printf("Info: %u\n", m_info);
    printf("Other: %u\n", m_other);
    printf("Section Header Index: %u\n", m_shndx);
    printf("Value: %lu\n", m_value);
    printf("Size: %lu\n", m_size);
}

SymbolTable::SymbolTable()
    : PartitionAbstract(0, 0), m_locNumEntries(0), m_entries(nullptr)
{
}

SymbolTable::SymbolTable(std::ifstream &inELFStream, size_t offset,
                             size_t size, bool lsb)
    : PartitionAbstract(offset, size), m_locNumEntries(size / PARTITION_SYMTAB_ENTRY_SIZE),
    m_locEntrySize(PARTITION_SYMTAB_ENTRY_SIZE)
{
    m_entries = std::make_unique<SymbolTableEntry[]>(m_locNumEntries);

    for (size_t entryIdx = 0; entryIdx < m_locNumEntries; ++entryIdx)
        m_entries[entryIdx] = SymbolTableEntry(inELFStream, offset + (entryIdx * m_locEntrySize), lsb);
}

void SymbolTable::print() const {
    printf("| --- Symbol Table --- |\n");
    printf("Location[Offset]: %lu\n", m_locOffset);
    printf("Location[Num Entries]: %lu\n", m_locNumEntries);
    printf("Location[Entry Size]: %lu\n", m_locEntrySize);
}