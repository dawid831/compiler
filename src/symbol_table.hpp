#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

enum class SymbolKind {
    VARIABLE,
    ARRAY
};

struct Symbol {
    SymbolKind kind;
    long long start;   // dla tablic
    long long end;     // dla tablic
};

class SymbolTable {
public:
    bool declareVariable(const std::string& name);
    bool declareArray(const std::string& name, long long start, long long end);

    const Symbol* lookup(const std::string& name) const;

    void dump() const; // debug
private:
    std::unordered_map<std::string, Symbol> table;
};
