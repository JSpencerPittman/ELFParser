#ifndef IDENTIFICATION_H_
#define IDENTIFICATION_H_

#include <fstream>
#include <optional>

#include "util/read_bin.h"

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

        size_t bytes() { return ELF_IDENT_LEN; }
        size_t begin() { return 0; }
        size_t end() { return ELF_IDENT_LEN; }

        // Getters
        Byte fileClass() const { return m_fileClass; }
        Byte dataEncoding() const { return m_dataEncoding; }
        Byte fileVersion() const { return m_fileVersion; }

    private:
        Byte m_fileClass;
        Byte m_dataEncoding;
        Byte m_fileVersion;
    };

}

#endif