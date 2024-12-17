#ifndef PARTITION_SECTION_HEADER_H_
#define PARTITION_SECTION_HEADER_H_

#include <fstream>
#include <memory>

#include "partition/partition.h"
#include "elf_types.h"
#include "util/iterator.hpp"

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

#define SHN_UNDEF 0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC 0xff00
#define SHN_HIPROC 0xff1f
#define SHN_LOOS 0xff20
#define SHN_HIOS 0xff3f
#define SHN_ABS 0xfff1
#define SHN_COMMON 0xfff2
#define SHN_XINDEX 0xffff
#define SHN_HIRESERVE 0xffff

namespace Partition
{
    class SectionHeaderEntry : public PartitionAbstract
    {
    public:
        SectionHeaderEntry();
        SectionHeaderEntry(std::ifstream &inELFStream, size_t offset, size_t entryBytes,
                           bool lsb);

        void print() const;

        // Getters
        Elf64_Word name() const { return m_name; };
        Elf64_Word type() const { return m_type; };
        Elf64_Xword flags() const { return m_flags; };
        Elf64_Addr addr() const { return m_addr; };
        Elf64_Off offset() const { return m_offset; };
        Elf64_Xword sectionBytes() const { return m_sectionBytes; };
        Elf64_Word link() const { return m_link; };
        Elf64_Word info() const { return m_info; };
        Elf64_Xword addralign() const { return m_addralign; };
        Elf64_Xword entsize() const { return m_entsize; };

    private:
        // Values
        Elf64_Word m_name;
        Elf64_Word m_type;
        Elf64_Xword m_flags;
        Elf64_Addr m_addr;
        Elf64_Off m_offset;
        Elf64_Xword m_sectionBytes;
        Elf64_Word m_link;
        Elf64_Word m_info;
        Elf64_Xword m_addralign;
        Elf64_Xword m_entsize;
    };

    class SectionHeader : public PartitionAbstract
    {
    public:
        SectionHeader();
        SectionHeader(std::ifstream &inELFStream, size_t offset, size_t size, size_t entryBytes, bool lsb);

        void print() const;

        // Iterator and element access
        const SectionHeaderEntry &operator[](size_t idx) const { return m_entries[idx]; }
        Iterator<const SectionHeaderEntry> begin() { return {m_entries.get()}; }
        Iterator<const SectionHeaderEntry> end() { return {m_entries.get() + m_locSize}; }
        size_t size() const { return m_locSize; }

    private:
        // Location
        size_t m_locSize;
        size_t m_locEntryBytes;

        // Values
        std::unique_ptr<SectionHeaderEntry[]> m_entries;
    };
};

#endif