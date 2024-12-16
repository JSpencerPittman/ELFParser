#ifndef PARTITION_SYMBOL_TABLE_H_
#define PARTITION_SYMBOL_TABLE_H_

#include <string>
#include <memory>

#include "elf_types.h"
#include "partition/partition.h"
#include "util/iterator.hpp"

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
        Elf64_Xword bytes() const { return m_bytes; };

    private:
        // Values
        Elf64_Word m_name;
        Byte m_info;
        Byte m_other;
        Elf64_Half m_shndx;
        Elf64_Addr m_value;
        Elf64_Xword m_bytes;
    };

    class SymbolTable : public PartitionAbstract
    {
    public:
        SymbolTable();
        SymbolTable(std::ifstream &inELFStream, size_t offset, size_t bytes, bool lsb, Elf64_Addr stringTableIdx);

        void print() const;

        // Iterator and element access
        const SymbolTableEntry &operator[](size_t idx) const { return m_entries[idx]; }
        Iterator<const SymbolTableEntry> begin() { return {m_entries.get()}; }
        Iterator<const SymbolTableEntry>  end() { return {m_entries.get() + m_locSize}; }
        size_t size() const { return m_locSize; }

        Elf64_Addr stringTableIdx() const { return m_stringTableIdx; }

    private:
        // Location
        size_t m_locSize;
        size_t m_locEntryBytes;

        // Values
        Elf64_Addr m_stringTableIdx; // Associated string table
        std::unique_ptr<SymbolTableEntry[]> m_entries;
    };
};

#endif