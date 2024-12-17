#include "resolve.h"

Symbols resolveSymbols(const ELFFile &elfFile, size_t symbolTableSectionIdx)
{
    const Partition::SymbolTable &symbolTable = elfFile.symbolTable(symbolTableSectionIdx);
    const Partition::StringTable &stringTable = elfFile.stringTable(symbolTable.stringTableIdx());

    size_t numSymbols = symbolTable.size();
    Symbols symbols(numSymbols);

    for(size_t symIdx = 0; symIdx < numSymbols; ++symIdx) {
        const Partition::SymbolTableEntry& symEntry = symbolTable[symIdx];
        symbols[symIdx].name(stringTable.read(symEntry.name()));
    }

    return symbols;
}

std::optional<std::string> resolveSymbolName(const Partition::SymbolTableEntry &entry,
                                             const Partition::StringTable &stringTable)
{
    if(entry.name() == 0)
        return {};
    else
        return stringTable.read(entry.name());
}