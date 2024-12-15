#ifndef STRING_TABLE_H_
#define STRING_TABLE_H_

#include <string>

#include "partition/section_header.h"

namespace Section
{
    class StringTable
    {
    public:
        StringTable();
        StringTable(const Partition::SectionHeaderEntry &headerEntry);

        std::string read(std::ifstream& inELFStream, size_t idx) const;

    private:
        // Location
        size_t m_locOffset;
        size_t m_locSize;
    };
};

#endif