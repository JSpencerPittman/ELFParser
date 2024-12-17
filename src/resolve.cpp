#include "resolve.h"

#include "util/binary.h"

Symbols resolveSymbols(const ELFFile &elfFile, size_t symbolTableSectionIdx)
{
    const Partition::SymbolTable &symbolTable = elfFile.symbolTable(symbolTableSectionIdx);
    const Partition::StringTable &stringTable = elfFile.stringTable(symbolTable.stringTableIdx());

    size_t numSymbols = symbolTable.size();
    Symbols symbols(numSymbols);

    for (size_t symIdx = 0; symIdx < numSymbols; ++symIdx)
    {
        const Partition::SymbolTableEntry &symEntry = symbolTable[symIdx];

        auto name = resolveSymbolName(symEntry, stringTable);
        auto bytes = resolveSymbolBytes(symEntry);

        symbols[symIdx] = Symbol(std::move(name), bytes);
    }

    return symbols;
}

std::optional<std::string> resolveSymbolName(const Partition::SymbolTableEntry &entry,
                                             const Partition::StringTable &stringTable)
{
    if (entry.name() == 0)
        return {};
    else
        return stringTable.read(entry.name());
}

std::optional<size_t> resolveSymbolBytes(const Partition::SymbolTableEntry &entry)
{
    if (entry.dataBytes() == 0)
        return {};
    else
        return entry.dataBytes();
}

bool isSpecialSection(size_t sectionIndex)
{
    switch (sectionIndex)
    {
    case SHN_UNDEF:
        return true;
    case SHN_LOPROC:
        return true;
    case SHN_HIPROC:
        return true;
    case SHN_LOOS:
        return true;
    case SHN_HIOS:
        return true;
    case SHN_ABS:
        return true;
    case SHN_COMMON:
        return true;
    case SHN_XINDEX:
        return true;
    default:
        return false;
    }
}