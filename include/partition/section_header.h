#ifndef SECTION_HEADER_H_
#define SECTION_HEADER_H_

#include <fstream>
#include <memory>

#include "partition/partition.h"
#include "elf_types.h"

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
        SectionHeader(std::ifstream& inELFStream, size_t offset, size_t numEntries, size_t entrySize, bool lsb);

        size_t bytes() const { return m_locNumEntries * m_locEntrySize; };
        size_t begin() const { return m_locOffset; }
        size_t end() const { return begin() + bytes(); };

        void print() const;

        SectionHeaderEntry* entries() { return m_entries.get(); }
        const SectionHeaderEntry& operator[](size_t idx) const { return m_entries[idx]; }

    private:
        size_t m_locOffset;
        size_t m_locNumEntries;
        size_t m_locEntrySize;

        std::unique_ptr<SectionHeaderEntry[]> m_entries;
    };
};

#endif