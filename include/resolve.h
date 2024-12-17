#ifndef RESOLVE_H_
#define RESOLVE_H_

#include <optional>
#include <string>

#include "elf_file.h"
#include "partition/symbol_table.h"
#include "symbol.h"

Symbols resolveSymbols(const ELFFile& elfFile, size_t symbolTableSectionIdx);

std::optional<std::string> resolveSymbolName(const Partition::SymbolTableEntry& entry,
                                             const Partition::StringTable& stringTable);
std::optional<size_t> resolveSymbolBytes(const Partition::SymbolTableEntry& entry);

bool isSpecialSection(size_t sectionIndex);

#endif