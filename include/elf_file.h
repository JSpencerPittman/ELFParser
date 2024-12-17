#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include <string>
#include <filesystem>
#include <map>

#include "partition/header.h"
#include "partition/section_header.h"
#include "partition/string_table.h"
#include "partition/symbol_table.h"

class ELFFile
{
public:
    // Constructor
    ELFFile(const std::filesystem::path &path);

    // Getters
    const std::filesystem::path &path() const { return m_path; }
    const Partition::Header &header() const { return m_header; }

    // String Table
    const std::map<size_t, Partition::StringTable> &stringTableMap() const { return m_stringTableMap; }
    const Partition::StringTable &stringTable(size_t idx) const { return m_stringTableMap.at(idx); }

    // Symbol Table
    const std::map<size_t, Partition::SymbolTable> &symbolTableMap() const { return m_symbolTableMap; }
    const Partition::SymbolTable &symbolTable(size_t idx) const { return m_symbolTableMap.at(idx); }

    // Section Header
    const Partition::SectionHeader &sectionHeader() const { return m_sectionHeader; };
    const Partition::SectionHeaderEntry &sectionHeaderEntry(size_t idx) const { return m_sectionHeader[idx]; };

    // Reading
    std::unique_ptr<Byte[]> read(size_t offset, size_t bytes) const;
    std::unique_ptr<Byte[]> readFromSection(size_t sectionIdx, size_t offset, size_t bytes) const;

private:
    void verifyIsExistentELFFile(const std::filesystem::path &path) const;

    // File stream
    std::ifstream open() const;

private:
    std::filesystem::path m_path;

    // Partitions
    Partition::Header m_header;
    Partition::SectionHeader m_sectionHeader;
    std::map<size_t, Partition::StringTable> m_stringTableMap;
    std::map<size_t, Partition::SymbolTable> m_symbolTableMap;
};

#endif