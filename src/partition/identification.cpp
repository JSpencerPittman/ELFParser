#include "partition/identification.h"

#include "util/exception.hpp"
#include "util/binary.h"

using namespace Partition;

Identification::Identification()
    : PartitionAbstract(PARTITION_IDENT_OFF, PARTITION_IDENT_SIZE), m_fileClass(0), m_dataEncoding(0),
      m_fileVersion(0) {}

Identification::Identification(std::ifstream &inELFStream)
{
    m_fileClass = readByte(inELFStream, PARTITION_IDENT_FILECLASS_SIZE, std::ios::beg);
    m_dataEncoding = readByte(inELFStream);
    m_fileVersion = readByte(inELFStream);
}

void Identification::print() const
{
    printf("| --- Identification --- |\n");
    printf("File Class: %d\n", m_fileClass);
    printf("Data Encoding: %d\n", m_dataEncoding);
    printf("File Version: %d\n", m_fileVersion);
}