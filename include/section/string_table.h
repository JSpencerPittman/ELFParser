#ifndef STRING_TABLE_H_
#define STRING_TABLE_H_

#include <string>
#include <map>
#include <memory>

#include "elf_types.h"

namespace Section
{
    class StringTable
    {
    public:
        StringTable();
        StringTable(std::ifstream &inELFStream, size_t offset, size_t sectionSize);

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