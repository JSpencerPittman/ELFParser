#include "section/string_table.h"

#include "util/binary.h"

using namespace Section;

StringTable::StringTable()
    : m_locOffset(0), m_locSize(0) {}

StringTable::StringTable(const Partition::SectionHeaderEntry &headerEntry)
    : m_locOffset(headerEntry.offset()), m_locSize(headerEntry.size())
{
    if (headerEntry.type() != SHT_STRTAB)
        throw std::runtime_error("Provided header entry is not representative of \
            a string table.");
}

std::string StringTable::read(std::ifstream& inELFStream, size_t idx) const {
    return std::move(readString(inELFStream, m_locOffset + idx, std::ios::beg));
};