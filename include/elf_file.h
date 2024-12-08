#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include <string>
#include <filesystem>

#include "partition/identification.h"

class ELFFile {
public:
    // Constructor
    ELFFile(const std::filesystem::path& path);

    // Getters
    const std::filesystem::path& path() const { return m_path; }
    const Partition::Identification& identification() const { return m_identification; }

private:
    void verifyIsExistentELFFile(const std::filesystem::path& path);

    // Parsers
    void readElfHeader();

    // File stream
    std::ifstream open();

private:
    std::filesystem::path m_path;
    Partition::Identification m_identification;
};

#endif