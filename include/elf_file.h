#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include <string>
#include <filesystem>

#include "partition/identification.h"
#include "partition/header.h"

class ELFFile {
public:
    // Constructor
    ELFFile(const std::filesystem::path& path);

    // Getters
    const std::filesystem::path& path() const { return m_path; }
    
    const Partition::Identification& identification() const { return m_identification; }
    const Partition::Header& header() const { return m_header; }

private:
    void verifyIsExistentELFFile(const std::filesystem::path& path);

    // File stream
    std::ifstream open();

private:
    std::filesystem::path m_path;

    // Partitions
    Partition::Identification m_identification;
    Partition::Header m_header;
};

#endif