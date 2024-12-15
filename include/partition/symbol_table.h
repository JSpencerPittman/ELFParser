#ifndef PARTITION_SYMBOL_TABLE_H_
#define PARTITION_SYMBOL_TABLE_H_

#include <string>
#include <memory>

#include "elf_types.h"
#include "partition/partition.h"

#define PARTITION_SYMTAB_ENTRY_SIZE 24

namespace Partition
{
    class SymbolTableEntry : public PartitionAbstract
    {
    public:
        SymbolTableEntry();
        SymbolTableEntry(std::ifstream &inELFStream, size_t offset, bool lsb);

        void print() const;

        // Getters
        Elf64_Word name() const { return m_name; };
        Byte info() const { return m_info; };
        Byte other() const { return m_other; };
        Elf64_Half shndx() const { return m_shndx; };
        Elf64_Addr value() const { return m_value; };
        Elf64_Xword size() const { return m_size; };

    private:
        // Values
        Elf64_Word m_name;
        Byte m_info;
        Byte m_other;
        Elf64_Half m_shndx;
        Elf64_Addr m_value;
        Elf64_Xword m_size;
    };

    class SymbolTable : public PartitionAbstract
    {
    public:
        SymbolTable();
        SymbolTable(std::ifstream &inELFStream, size_t offset, size_t size, bool lsb, Elf64_Addr stringTableIdx);

        void print() const;

        size_t numEntries() const { return m_locNumEntries; }
        SymbolTableEntry *entries() { return m_entries.get(); }
        const SymbolTableEntry &operator[](size_t idx) const { return m_entries[idx]; }

        Elf64_Addr stringTableIdx() const { return m_stringTableIdx; } 

    private:
        // Location
        size_t m_locNumEntries;
        size_t m_locEntrySize;

        // Values
        Elf64_Addr m_stringTableIdx; // Associated string table
        std::unique_ptr<SymbolTableEntry[]> m_entries;
    };
};

#endif