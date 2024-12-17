#include "symbol.h"

Symbol::Symbol()
    : m_name("") {}

Symbol::Symbol(const std::string &name)
    : m_name(name) {}

void Symbol::print() const
{
    printf("| --- Symbol --- |\n");
    printf("Name: %s\n", nameOrDefault().c_str());
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
    for(auto symItr : (*this)) symItr.print();
}