#include <cstdio>

#include "elf_file.h"
#include "util/binary.h"

template<typename T>
void testme() {
    printf("SIZE: %lu\n", sizeof(T));
}

int main() {
    ELFFile("./../sample/sample");
}
