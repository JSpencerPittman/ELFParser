#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <memory>

#include "partition/symbol_table.h"
#include "partition/string_table.h"
#include "symbol.h"

class SymbolTable
{
public:
    SymbolTable();
    SymbolTable(const Partition::SymbolTable &partSymTab, const Partition::StringTable &partStrTab);

    Symbol *symbols() { return m_symbols.get(); }
    Symbol *begin() { return m_symbols.get(); }
    Symbol *end() { return m_symbols.get() + m_numSymbols; }

    size_t numSymbols() const { return m_numSymbols; }

private:
    size_t m_numSymbols;
    std::unique_ptr<Symbol[]> m_symbols;
};

#endif