#include <cstdio>

#include "elf_file.h"
#include "util/binary.h"
#include "symbol.h"
#include "resolve.h"

int main()
{
    ELFFile elfFile("./../sample/sample");

    for(auto& partSymTab : elfFile.symbolTableMap()) {
        printf("Symbol Table: %lu\n", partSymTab.first);

        Symbols symbols = resolveSymbols(elfFile, partSymTab.first);
        symbols.print();
        symbols.printSymbols();
    }
}
