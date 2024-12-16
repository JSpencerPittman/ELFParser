#include "symbol.h"

Symbol::Symbol()
    : m_name("") {}

Symbol::Symbol(const std::string& name)
    : m_name(name) {}

void Symbol::print() const {
    printf("| --- Symbol --- |\n");
    printf("Name: %s\n", m_name.c_str());
}