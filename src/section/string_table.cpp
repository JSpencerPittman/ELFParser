#include "section/string_table.h"

#include "util/binary.h"

using namespace Section;

StringTable::StringTable()
    : m_locOffset(0), m_locSize(0), m_contiguousStringArray(nullptr) {}

StringTable::StringTable(const Partition::SectionHeaderEntry &headerEntry,
                         std::ifstream &inELFStream)
    : m_locOffset(headerEntry.offset()), m_locSize(headerEntry.size())
{
    if (headerEntry.type() != SHT_STRTAB)
        throw std::runtime_error("Provided header entry is not representative of \
            a string table.");

    // Load section into memory
    m_contiguousStringArray = readByteArray(inELFStream, m_locSize,
                                            m_locOffset, std::ios::beg);

    // Save string sizes
    size_t lastNonNULLIdx = 0;
    for(size_t idx = 0; idx < m_locSize; ++idx)
        if(m_contiguousStringArray[idx] == 0) {
            m_stringSizeMap[lastNonNULLIdx] = idx - lastNonNULLIdx + 1;
            lastNonNULLIdx = idx+1;
        }
}

std::string StringTable::read(size_t idx) const {
    auto stringSizeItr = m_stringSizeMap.find(idx);
    if(stringSizeItr == m_stringSizeMap.end())
        throw std::runtime_error("Invalid idx provided to string table.\n");

    return {reinterpret_cast<char*>(m_contiguousStringArray.get() + idx), stringSizeItr->second};
}

void StringTable::print() const {
    printf("| --- String Table --- |\n");
    for(auto& entry: m_stringSizeMap)
        printf("%lu: %s\n", entry.first, read(entry.first).c_str());
}