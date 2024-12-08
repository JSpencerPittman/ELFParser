#ifndef ELF_FILE_H_
#define ELF_FILE_H_

#include <string>
#include <filesystem>

struct ELFIdentification {};

class ELFFile {
public:
    // Constructor
    ELFFile(const std::filesystem::path& path);

    // Getters
    const std::filesystem::path& path() const { return m_path; }

private:
    void verifyIsExistentELFFile(const std::filesystem::path& path);

    // Parsers
    void readElfHeader();

    // File stream
    std::ifstream open();

private:
    std::filesystem::path m_path;
};

#endif