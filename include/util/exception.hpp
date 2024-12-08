#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include<string>
#include<memory>

template <typename... Types>
std::string formatErrorMessage(const std::string& format, Types... args)
{
    int size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
    if(size < 0) throw std::runtime_error("Error during string formatting.");
    auto usize = static_cast<size_t>(size);
    auto buffer = std::make_unique<char[]>(usize);
    std::snprintf(buffer.get(), usize, format.c_str(), args ...);
    return {buffer.get(), buffer.get() + usize - 1};
}

template<typename T, typename ... Types>
void throwException(const std::string& format, Types ... args) {
    std::string errorMessage = formatErrorMessage(format, args ...);
    throw T(std::move(errorMessage));
}

#endif