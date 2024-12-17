#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <string>
#include <memory>
#include <optional>

#include "partition/symbol_table.h"
#include "partition/string_table.h"
#include "util/iterator.hpp"

#define SYMBOL_DEFAULT_NAME "NA"
#define SYMBOL_DEFAULT_BYTES 0

class Symbol
{
public:
    Symbol(const std::optional<std::string> &name = std::nullopt,
           std::optional<size_t> bytes = std::nullopt);

    void print() const;

    // Setters
    void name(const std::optional<std::string> &name) { m_name = name; }
    void bytes(const std::optional<std::size_t> &bytes) { m_bytes = bytes; }

    // Getter with defaults
    std::string nameOrDefault() const { return m_name.value_or(SYMBOL_DEFAULT_NAME); }
    size_t bytesOrDefault() const { return m_bytes.value_or(SYMBOL_DEFAULT_BYTES); }

    // Getter
    const std::optional<std::string> &name() const { return m_name; }
    const std::optional<size_t> &bytes() const { return m_bytes; }

    // Resolved
    bool nameResolved() const { return m_name.has_value(); }
    bool bytesResolved() const { return m_bytes.has_value(); }

private:
    std::optional<std::string> m_name; // Name of the symbol
    std::optional<size_t> m_bytes;     // Number of bytes
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

    Symbol &operator[](size_t idx) { return m_symbols[idx]; }
    const Symbol &operator[](size_t idx) const { return m_symbols[idx]; }

    size_t size() const { return m_size; }

private:
    size_t m_size;
    std::unique_ptr<Symbol[]> m_symbols;
};

#endif