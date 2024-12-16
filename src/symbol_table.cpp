#include "symbol_table.h"

SymbolTable::SymbolTable()
    : m_numSymbols(0), m_symbols(nullptr) {}

SymbolTable::SymbolTable(const Partition::SymbolTable &partSymTab, const Partition::StringTable &partStrTab)
    : m_numSymbols(partSymTab.size()),
      m_symbols(std::make_unique<Symbol[]>(partSymTab.size()))
{
    partStrTab.printTable();

    for (size_t idx = 0; idx < partSymTab.size(); ++idx)
    {
        const Partition::SymbolTableEntry &entry = partSymTab[idx];
        printf("Read(%lu): %u\n", idx, entry.name());
        std::string symbolName = partStrTab.read(entry.name());
        printf("Name: %s\n", symbolName.c_str());
        m_symbols[idx] = Symbol(std::move(symbolName));
    }
}