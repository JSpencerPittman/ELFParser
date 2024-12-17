#include "symbol.h"

Symbol::Symbol(const std::optional<std::string>& name, std::optional<size_t> bytes)
    : m_name(name), m_bytes(bytes) {}

void Symbol::print() const
{
    printf("| --- Symbol --- |\n");
    printf("Name: %s\n", nameOrDefault().c_str());
    printf("Bytes: %lu\n", bytesOrDefault());
}

Symbols::Symbols()
    : m_size(0), m_symbols(nullptr) {}

Symbols::Symbols(size_t size)
    : m_size(size),
      m_symbols(std::make_unique<Symbol[]>(size))
{
}

void Symbols::print() const
{
    printf("| --- Symbols --- |\n");
    printf("Size: %lu\n", m_size);
}

void Symbols::printSymbols() const
{
    printf("| --- Symbols [Listed] --- |\n");
    for(const auto& symItr : (*this)) symItr.print();
}