#ifndef IDENTIFICATION_H_
#define IDENTIFICATION_H_

#include <fstream>

#include "partition/partition.h"
#include "elf_types.h"
#include "util/binary.h"

#define PARTITION_IDENT_FILECLASS_SIZE 4
#define PARTITION_IDENT_SIZE 16
#define PARTITION_IDENT_OFF 0

namespace Partition
{

    class Identification : public PartitionAbstract
    {
    public:
        Identification();
        Identification(std::ifstream &inELFStream);

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