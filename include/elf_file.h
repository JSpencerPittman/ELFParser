#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include <string>
#include <filesystem>

#include "partition/header.h"
#include "partition/section_header.h"

class ELFFile {
public:
    // Constructor
    ELFFile(const std::filesystem::path& path);

    // Getters
    const std::filesystem::path& path() const { return m_path; }
    
    const Partition::Header& header() const { return m_header; }

private:
    void verifyIsExistentELFFile(const std::filesystem::path& path);

    // File stream
    std::ifstream open();

private:
    std::filesystem::path m_path;

    // Partitions
    Partition::Header m_header;
    Partition::SectionHeader m_sectionHeader;
};

#endif