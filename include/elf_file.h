#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include <string>
#include <filesystem>
#include <map>

#include "partition/header.h"
#include "partition/section_header.h"
#include "partition/string_table.h"
#include "partition/symbol_table.h"

class ELFFile {
public:
    // Constructor
    ELFFile(const std::filesystem::path& path);

    // Getters
    const std::filesystem::path& path() const { return m_path; }
    
    const Partition::Header& header() const { return m_header; }
    const Partition::SectionHeader& sectionHeader() const { return m_sectionHeader; };
    const std::map<size_t, Partition::StringTable>& stringTableMap() const { return m_stringTableMap; }
    const std::map<size_t, Partition::SymbolTable>& symbolTableMap() const { return m_symbolTableMap; }

private:
    void verifyIsExistentELFFile(const std::filesystem::path& path);

    // File stream
    std::ifstream open();

private:
    std::filesystem::path m_path;

    // Partitions
    Partition::Header m_header;
    Partition::SectionHeader m_sectionHeader;
    std::map<size_t, Partition::StringTable> m_stringTableMap;
    std::map<size_t, Partition::SymbolTable> m_symbolTableMap;
};

#endif