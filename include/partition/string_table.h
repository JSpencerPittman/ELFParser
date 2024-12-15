#ifndef PARTITION_STRING_TABLE_H_
#define PARTITION_STRING_TABLE_H_

#include <string>
#include <map>
#include <memory>

#include "elf_types.h"
#include "partition/partition.h"


namespace Partition
{
    class StringTable : public PartitionAbstract
    {
    public:
        StringTable();
        StringTable(std::ifstream &inELFStream, size_t offset, size_t size);

        std::string read(size_t idx) const;

        void print() const;
        void printTable() const;

    private:
        // Location
        size_t m_locNumEntries;

        // Storage
        std::map<size_t, size_t> m_stringSizeMap;
        std::unique_ptr<Byte[]> m_contiguousStringArray;
    };
};

#endif