#include <cstdio>

#include "elf_file.h"
#include "util/binary.h"

template<typename T>
void testme() {
    printf("SIZE: %lu\n", sizeof(T));
}

int main() {
    ELFFile elfFile("./../sample/sample");

    for(auto& strtab : elfFile.stringTableMap()) {
        printf("String Table at %lu\n", strtab.first);
        strtab.second.printTable();
    }
    for(auto& symtab : elfFile.symbolTableMap())
        printf("Symbol Table: %lu\n", symtab.first);
}
