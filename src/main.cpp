#include <cstdio>

#include "elf_file.h"
#include "util/binary.h"
#include "symbol.h"

template <typename T>
void testme()
{
    printf("SIZE: %lu\n", sizeof(T));
}

int main()
{
    ELFFile elfFile("./../sample/sample");

    for(auto& partSymTab : elfFile.symbolTableMap()) {
        printf("Symbol Table: %lu\n", partSymTab.first);

        auto& partStrTab = elfFile.stringTable(partSymTab.second.stringTableIdx());
        Symbols symbols(partSymTab.second, partStrTab);

        printf("There are %lu symbols\n", symbols.size());
        // for(auto& symbol : symtab) {
        //     symbol.print();
        // }
    }
}
