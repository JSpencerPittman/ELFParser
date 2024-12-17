#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <string>
#include <memory>

#include "partition/symbol_table.h"
#include "partition/string_table.h"
#include "util/iterator.hpp"

class Symbol
{
public:
    Symbol();
    Symbol(const std::string& name);

    void print() const;

    // Getters
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

class Symbols
{
public:
    Symbols();
    Symbols(const Partition::SymbolTable &partSymTab, const Partition::StringTable &partStrTab);

    // Access
    Iterator<const Symbol> begin() const { return Iterator<const Symbol>(m_symbols.get()); }
    Iterator<const Symbol> end() const { return Iterator<const Symbol>(m_symbols.get() + m_size); }
    const Symbol& operator[](size_t idx) const { return m_symbols[idx]; }

    size_t size() const { return m_size; }

private:
    size_t m_size;
    std::unique_ptr<Symbol[]> m_symbols;
};

#endif