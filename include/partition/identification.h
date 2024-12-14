#ifndef IDENTIFICATION_H_
#define IDENTIFICATION_H_

#include <fstream>
#include <optional>

#include "elf_types.h"
#include "util/binary.h"

typedef unsigned char Byte;

#define ELF_IDENT_FCLASS_OFF 4
#define ELF_IDENT_LEN 16

namespace Partition
{

    class Identification
    {
    public:
        Identification();
        Identification(std::ifstream &inELFStream);

        size_t bytes() const { return ELF_IDENT_LEN; }
        size_t begin() const { return 0; }
        size_t end() const { return ELF_IDENT_LEN; }

        void print() const;

        // Getters
        Byte fileClass() const { return m_fileClass; }
        Byte dataEncoding() const { return m_dataEncoding; }
        Byte fileVersion() const { return m_fileVersion; }

        bool lsb() const { return m_dataEncoding == 1;}
        bool msb() const { return m_dataEncoding == 2;}

    private:
        Byte m_fileClass;
        Byte m_dataEncoding;
        Byte m_fileVersion;
    };

}

#endif