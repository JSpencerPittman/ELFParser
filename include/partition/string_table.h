#ifndef PARTITION_STRING_TABLE_H_
#define PARTITION_STRING_TABLE_H_

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "elf_types.h"
#include "partition/partition.h"


namespace Partition
{
    class StringTable : public PartitionAbstract
    {
    public:
        StringTable();
        StringTable(std::ifstream &inELFStream, size_t offset, size_t bytes);

        std::string read(size_t idx) const;

        void print() const;
        void printTable() const;

        size_t size() const { return m_locSize; }

    private:
        std::string readAtIndex(size_t idx) const;

    private:
        // Location
        size_t m_locSize;

        // Storage
        std::vector<int> m_idxs;
        std::map<size_t, size_t> m_stringSizeMap;
        std::unique_ptr<Byte[]> m_contiguousStringArray;
    };
};

#endif