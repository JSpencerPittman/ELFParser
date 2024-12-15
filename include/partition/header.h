#ifndef HEADER_H_
#define HEADER_H_

#include <fstream>
#include <optional>

#include "partition/partition.h"
#include "elf_types.h"

#define PARTITION_HEADER_OFF 16
#define PARTITION_HEADER_SIZE 48

namespace Partition
{

    class Header : public Partition
    {
    public:
        Header();
        Header(std::ifstream &inELFStream, bool lsb);

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
        // Values
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