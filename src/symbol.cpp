#include "symbol.h"

Symbol::Symbol()
    : m_name("") {}

Symbol::Symbol(const std::string& name)
    : m_name(name) {}

void Symbol::print() const {
    printf("| --- Symbol --- |\n");
    printf("Name: %s\n", m_name.c_str());
}

Symbols::Symbols()
    : m_size(0), m_symbols(nullptr) {}

Symbols::Symbols(const Partition::SymbolTable &partSymTab, const Partition::StringTable &partStrTab)
    : m_size(partSymTab.size()),
      m_symbols(std::make_unique<Symbol[]>(partSymTab.size()))
{
    // partStrTab.printTable();

    for (size_t idx = 0; idx < partSymTab.size(); ++idx)
    {
        const Partition::SymbolTableEntry &entry = partSymTab[idx];
        // entry.print();

        printf("Read(%lu): %u, section index: %u, with size: %u\n", idx, entry.name(), entry.shndx(), entry.dataBytes());
        // std::string symbolName = partStrTab.read(entry.name());
        // printf("Name: %s\n", symbolName.c_str());
        // m_symbols[idx] = Symbol(std::move(symbolName));
    }
}