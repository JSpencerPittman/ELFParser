#include "partition/symbol_table.h"

#include "util/binary.h"

using namespace Partition;

SymbolTableEntry::SymbolTableEntry()
    : PartitionAbstract(0, 0), m_name(0), m_info(0), m_other(0), m_shndx(0), m_value(0), m_dataBytes(0),
      m_bind(0), m_type(0)
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
    m_dataBytes = readAndReinterpretByteArray<Elf64_Xword>(inELFStream, lsb);
    m_bind = m_info >> 4;
    m_type = m_info & 0xf;
}

void SymbolTableEntry::print() const
{
    printf("| --- Symbol Table Entry --- |\n");
    printLocation();
    printf("Name: %u\n", m_name);
    printf("Info: %u\n", m_info);
    printf("Other: %u\n", m_other);
    printf("Section Header Index: %u\n", m_shndx);
    printf("Value: %lu\n", m_value);
    printf("Size: %lu\n", m_dataBytes);
    printf("Bind: %u\n", m_bind);
    printf("Type: %u\n", m_type);
}

SymbolTable::SymbolTable()
    : PartitionAbstract(0, 0), m_locSize(0), m_locEntryBytes(0), m_stringTableIdx(0),
      m_entries(nullptr)
{
}

SymbolTable::SymbolTable(std::ifstream &inELFStream, size_t offset,
                         size_t bytes, bool lsb, Elf64_Addr stringTableIdx)
    : PartitionAbstract(offset, bytes), m_locSize(bytes / PARTITION_SYMTAB_ENTRY_SIZE),
      m_locEntryBytes(PARTITION_SYMTAB_ENTRY_SIZE), m_stringTableIdx(stringTableIdx)
{
    m_entries = std::make_unique<SymbolTableEntry[]>(m_locSize);

    for (size_t entryIdx = 0; entryIdx < m_locSize; ++entryIdx)
        m_entries[entryIdx] = SymbolTableEntry(inELFStream, offset + (entryIdx * m_locEntryBytes), lsb);
}

void SymbolTable::print() const
{
    printf("| --- Symbol Table --- |\n");
    printLocation();
    printf("Location[Size]: %lu\n", m_locSize);
    printf("Location[Entry Bytes]: %lu\n", m_locEntryBytes);
    printf("String Table Index: %lu\n", m_stringTableIdx);
}
