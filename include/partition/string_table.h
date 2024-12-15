#ifndef STRING_TABLE_H_
#define STRING_TABLE_H_

#include <string>
#include <map>
#include <memory>

#include "elf_types.h"
#include "partition/partition.h"


namespace Partition
{
    class StringTable : public Partition
    {
    public:
        StringTable();
        StringTable(std::ifstream &inELFStream, size_t offset, size_t sectionSize);

        std::string read(size_t idx) const;

        size_t bytes() const { return m_locSize; }
        size_t begin() const { return m_locOffset; }
        size_t end() const { return begin() + bytes(); }

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