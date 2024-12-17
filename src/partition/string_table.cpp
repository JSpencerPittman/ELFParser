#include "partition/string_table.h"

#include "util/binary.h"

using namespace Partition;

StringTable::StringTable()
    : PartitionAbstract(0, 0), m_locSize(0), m_contiguousStringArray(nullptr) {}

StringTable::StringTable(std::ifstream &inELFStream, size_t offset, size_t bytes)
    : PartitionAbstract(offset, bytes)
{
    // Load section into memory
    m_contiguousStringArray = readByteArray(inELFStream, m_locBytes,
                                            m_locOffset, std::ios::beg);

    // Save string sizes
    size_t idx = 0;
    while(idx < m_locBytes) {
        std::string str = readAtIndex(idx);
        m_stringSizeMap[idx] = str.size();
        m_idxs.emplace_back(idx);
        idx += str.size();
    }

    m_locSize = m_stringSizeMap.size();
}

std::string StringTable::read(size_t idx) const {
    auto stringSizeItr = m_stringSizeMap.find(idx);
    if(stringSizeItr == m_stringSizeMap.end())
        return readAtIndex(idx);
    return {reinterpret_cast<char*>(m_contiguousStringArray.get() + idx), stringSizeItr->second};
}

void StringTable::print() const {
    printf("| --- String Table --- |\n");
    printLocation();
    printf("Location[Size]: %lu\n", m_locSize);
}

void StringTable::printTable() const {
    printf("String Table Contents\n");
    for(auto& entry: m_stringSizeMap)
        printf("%lu: %s\n", entry.first, read(entry.first).c_str());
}

std::string StringTable::readAtIndex(size_t idx) const {
    size_t size = 0;
    while(m_contiguousStringArray[idx + size] != 0 && idx + size < m_locBytes) ++size;
    if(idx + size >= m_locBytes)
        throw std::runtime_error("Index is out of bounds.\n"); 

    return {reinterpret_cast<char*>(m_contiguousStringArray.get() + idx), size+1};
}