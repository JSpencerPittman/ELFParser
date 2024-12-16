#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <string>

class Symbol
{
public:
    Symbol();
    Symbol(const std::string& name);

    void print() const;

    // Getters
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

#endif