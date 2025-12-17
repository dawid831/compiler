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
    long long start, end;
    int uid;
    int addr = -1;
    char mode;
    bool initialized;
};

class SymbolTable {
    std::vector<std::unordered_map<std::string, Symbol>> scopes;
    std::unordered_map<int, Symbol> uidMap;
    int nextUid = 1;
public:
    std::unordered_map<int, Symbol>& getUidMap() { return uidMap; }
    const std::unordered_map<int, Symbol>& getUidMap() const { return uidMap; }

    void dumpWithAddrs() const;
    void dumpNamesUidsAddrs() const;

    SymbolTable() { enterScope(); }

    void enterScope();
    void leaveScope();

    bool declareVariable(const std::string& name, char mode = ' ', bool initialized = true);
    bool declareArray(const std::string& name, long long start, long long end, char mode = 'T');

    const Symbol* lookup(const std::string& name) const;
    Symbol* lookupMutable(const std::string& name);

    std::vector<Symbol>& getAllSymbols();
    const std::vector<Symbol>& getAllSymbols() const;

    const Symbol* lookupByUid(int uid) const;

    void dump() const;
};

