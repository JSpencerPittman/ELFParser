#ifndef SECTION_HEADER_H_
#define SECTION_HEADER_H_

#include <fstream>

#include "partition/partition.h"

namespace Partition
{
    class SectionHeader : public Partition
    {
    public:
        SectionHeader();
        SectionHeader(std::ifstream& inELFStream, size_t offset, size_t numEntries, size_t entrySize);

        size_t bytes() const { return m_numEntries * m_entrySize; };
        size_t begin() const { return m_offset; }
        size_t end() const { return begin() + bytes(); };

        virtual void print() const = 0;
    
    private:
        size_t m_offset;
        size_t m_numEntries;
        size_t m_entrySize;
    };
};

#endif