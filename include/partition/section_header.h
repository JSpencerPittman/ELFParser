#ifndef SECTION_HEADER_H_
#define SECTION_HEADER_H_

#include <fstream>
#include <memory>

#include "partition/partition.h"
#include "elf_types.h"

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_INIT_ARRAY 14
#define SHT_FINI_ARRAY 15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP 17
#define SHT_SYMTAB_SHNDX 18
#define SHT_LOOS 0x60000000
#define SHT_HIOS 0x6fffffff
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xffffffff

namespace Partition
{
    class SectionHeaderEntry : public Partition
    {
    public:
        SectionHeaderEntry();
        SectionHeaderEntry(std::ifstream &inELFStream, size_t offset, size_t entrySize,
                           bool lsb);

        size_t bytes() const { return m_locEntrySize; };
        size_t begin() const { return m_locOffset; }
        size_t end() const { return begin() + bytes(); };

        void print() const;

        // Getters
        Elf64_Word name() const { return m_name; };
        Elf64_Word type() const { return  m_type; };
        Elf64_Xword flags() const { return m_flags; };
        Elf64_Addr addr() const { return m_addr; };
        Elf64_Off offset() const { return m_offset; };
        Elf64_Xword size() const { return m_size; };
        Elf64_Word link() const { return m_link; };
        Elf64_Word info() const { return m_info; };
        Elf64_Xword addralign() const { return m_addralign; };
        Elf64_Xword entsize() const { return m_entsize; };

    private:
        // Location
        size_t m_locOffset;
        size_t m_locEntrySize;

        // Values
        Elf64_Word m_name;
        Elf64_Word m_type;
        Elf64_Xword m_flags;
        Elf64_Addr m_addr;
        Elf64_Off m_offset;
        Elf64_Xword m_size;
        Elf64_Word m_link;
        Elf64_Word m_info;
        Elf64_Xword m_addralign;
        Elf64_Xword m_entsize;
    };

    class SectionHeader : public Partition
    {
    public:
        SectionHeader();
        SectionHeader(std::ifstream &inELFStream, size_t offset, size_t numEntries, size_t entrySize, bool lsb);

        size_t bytes() const { return m_locNumEntries * m_locEntrySize; };
        size_t begin() const { return m_locOffset; }
        size_t end() const { return begin() + bytes(); };

        void print() const;

        size_t numEntries() const { return m_locNumEntries; }
        SectionHeaderEntry *entries() { return m_entries.get(); }
        const SectionHeaderEntry &operator[](size_t idx) const { return m_entries[idx]; }

    private:
        // Location
        size_t m_locOffset;
        size_t m_locNumEntries;
        size_t m_locEntrySize;

        // Values
        std::unique_ptr<SectionHeaderEntry[]> m_entries;
    };
};

#endif