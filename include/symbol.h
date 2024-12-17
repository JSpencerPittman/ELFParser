#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <string>
#include <memory>
#include <optional>

#include "partition/symbol_table.h"
#include "partition/string_table.h"
#include "util/iterator.hpp"

class Symbol
{
public:
    Symbol();
    Symbol(const std::string& name);

    void print() const;

    // Setters
    void name(const std::string& name) { m_name = name; }

    // Value or default
    std::string nameOrDefault() const { return m_name.value_or("NA"); }

    // Value
    const std::optional<std::string>& name() const { return m_name; }

    // Resolved
    bool nameResolved() const { return m_name.has_value(); }

private:
    std::optional<std::string> m_name; // Name of the symbol
};

class Symbols
{
public:
    Symbols();
    Symbols(size_t size);

    void print() const;
    void printSymbols() const;

    // Access
    Iterator<Symbol> begin() { return {m_symbols.get()}; }
    Iterator<const Symbol> begin() const { return {m_symbols.get()}; }

    Iterator<Symbol> end() { return {m_symbols.get() + m_size}; }
    Iterator<const Symbol> end() const { return {m_symbols.get() + m_size}; }

    Symbol& operator[](size_t idx) { return m_symbols[idx]; }
    const Symbol& operator[](size_t idx) const { return m_symbols[idx]; }

    size_t size() const { return m_size; }

private:
    size_t m_size;
    std::unique_ptr<Symbol[]> m_symbols;
};

#endif