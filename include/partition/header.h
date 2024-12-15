#ifndef PARTITION_HEADER_H_
#define PARTITION_HEADER_H_

#include <fstream>
#include <optional>

#include "partition/partition.h"
#include "elf_types.h"


#define PARTITION_HEADER_IDENT_MAGIC_SIZE 4
#define PARTITION_HEADER_IDENT_SIZE 16
#define PARTITION_HEADER_OFF 0
#define PARTITION_HEADER_SIZE 64

namespace Partition
{

    class Header : public PartitionAbstract
    {
    public:
        Header();
        Header(std::ifstream &inELFStream);

        void print() const;

        // Getters
        Byte fileClass() const { return m_fileClass; }
        Byte dataEncoding() const { return m_dataEncoding; }
        Byte fileVersion() const { return m_fileVersion; }
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

        bool lsb() const { return m_dataEncoding == 1;}
        bool msb() const { return m_dataEncoding == 2;}

    private:
        // Values
        Byte m_fileClass;
        Byte m_dataEncoding;
        Byte m_fileVersion;
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