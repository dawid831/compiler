#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

enum class SymbolKind {
    VARIABLE,
    ARRAY
};

struct Symbol {
    SymbolKind kind;
    long long start;   // dla tablic
    long long end;     // dla tablic
    int uid;
};

class SymbolTable {
    std::vector<std::unordered_map<std::string, Symbol>> scopes;
    int nextUid = 1;
public:
    SymbolTable() { enterScope(); } // globalny scope

    void enterScope();
    void leaveScope();

    bool declareVariable(const std::string& name);
    bool declareArray(const std::string& name, long long start, long long end);

    const Symbol* lookup(const std::string& name) const;

    void dump() const;
};
