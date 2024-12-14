#include "partition/identification.h"

#include "util/exception.hpp"
#include "util/binary.h"

using namespace Partition;

Identification::Identification()
    : m_fileClass(0), m_dataEncoding(0), m_fileVersion(0) {}

Identification::Identification(std::ifstream &inELFStream)
{
    m_fileClass = readByte(inELFStream, ELF_IDENT_FCLASS_OFF, std::ios::beg);
    m_dataEncoding = readByte(inELFStream);
    m_fileVersion = readByte(inELFStream);
}

void Identification::print() const {
    printf("| --- Identification --- |\n");
    printf("File Class: %d\n", m_fileClass);
    printf("Data Encoding: %d\n", m_dataEncoding);
    printf("File Version: %d\n", m_fileVersion);
}