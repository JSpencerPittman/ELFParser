#include <cstdio>

#include "elf_file.h"
#include "util/binary.h"
#include "symbol_table.h"

template <typename T>
void testme()
{
    printf("SIZE: %lu\n", sizeof(T));
}

int main()
{
    ELFFile elfFile("./../sample/sample");

    // for(const auto& stringTableEntry : elfFile.stringTableMap()) {
    //     printf("String Table(%lu)\n", stringTableEntry.first);
    //     stringTableEntry.second.printTable();
    //     printf("Size: %lu\n", stringTableEntry.second.size());
    // }

    for(auto& partSymTab : elfFile.symbolTableMap()) {
        printf("Symbol Table: %lu\n", partSymTab.first);

        auto& partStrTab = elfFile.stringTable(partSymTab.second.stringTableIdx());
        SymbolTable symtab(partSymTab.second, partStrTab);

        printf("There are %lu symbols\n", symtab.numSymbols());
        for(auto& symbol : symtab) {
            symbol.print();
        }
    }

    // auto& partSymTab = elfFile.symbolTable(28);
    // auto &partStrTab = elfFile.stringTable(partSymTab.stringTableIdx());

    // printf("String Table:\n");
    // partStrTab.printTable();

    // SymbolTable symtab(partSymTab, partStrTab);

    // printf("There are %lu symbols\n", symtab.numSymbols());
    // for (auto &symbol : symtab)
    // {
    //     symbol.print();
    // }
}
