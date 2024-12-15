#ifndef STRING_TABLE_H_
#define STRING_TABLE_H_

#include <string>
#include <map>

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

        void print() const;

    private:
        // Location
        size_t m_locOffset;
        size_t m_locSize;

        // Storage
        std::map<size_t, size_t> m_stringSizeMap;
        std::unique_ptr<Byte[]> m_contiguousStringArray;
    };
};

#endif