#ifndef HEADER_H_
#define HEADER_H_

#include <fstream>
#include <optional>

#include "partition/partition.h"
#include "elf_types.h"

typedef unsigned char Byte;

namespace Partition
{

    class Header : public Partition
    {
    public:
        Header();
        Header(std::ifstream &inELFStream, size_t offset, bool lsb);

        size_t bytes() const { return m_ehsize; }
        size_t begin() const { return m_offset; }
        size_t end() const { return m_offset + m_ehsize; }

        void print() const;

        // Getters
        Elf64_Half type() const { return m_type;}
        Elf64_Half machine() const { return m_machine;}
        Elf64_Word version() const { return m_version;}
        Elf64_Addr entry() const { return m_entry;}
        Elf64_Off phoff() const { return m_phoff;}
        Elf64_Off shoff() const { return m_shoff;}
        Elf64_Word flags() const { return m_flags;}
        Elf64_Half ehsize() const { return m_ehsize;}
        Elf64_Half phentsize() const { return m_phentsize;}
        Elf64_Half phnum() const { return m_phnum;}
        Elf64_Half shentsize() const { return m_shentsize;}
        Elf64_Half shnum() const { return m_shnum;}
        Elf64_Half shstrndx() const { return m_shstrndx;}

    private:
        size_t m_offset;

        Elf64_Half m_type;
        Elf64_Half m_machine;
        Elf64_Word m_version;
        Elf64_Addr m_entry;
        Elf64_Off m_phoff;
        Elf64_Off m_shoff;
        Elf64_Word m_flags;
        Elf64_Half m_ehsize;
        Elf64_Half m_phentsize;
        Elf64_Half m_phnum;
        Elf64_Half m_shentsize;
        Elf64_Half m_shnum;
        Elf64_Half m_shstrndx;
    };

}

#endif