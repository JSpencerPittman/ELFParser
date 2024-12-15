#ifndef STRING_TABLE_H_
#define STRING_TABLE_H_

#include <string>
#include <unordered_map>

#include "partition/section_header.h"

namespace Section
{
    class StringTable
    {
    public:
        StringTable();
        StringTable(const Partition::SectionHeaderEntry &headerEntry,
                    std::ifstream &inELFStream);

        std::string read(size_t idx) const;

    private:
        // Location
        size_t m_locOffset;
        size_t m_locSize;

        // Storage
        std::unordered_map<size_t, size_t> m_stringSizeMap;
        std::unique_ptr<Byte[]> m_contiguousStringArray;
    };
};

#endif