#include "symbol_table.hpp"

void SymbolTable::enterScope() {
    scopes.emplace_back();
}

void SymbolTable::leaveScope() {
    if (!scopes.empty())
        scopes.pop_back();
}

bool SymbolTable::declareVariable(const std::string& name, char mode, bool initialized) {
    auto& scope = scopes.back();
    if (scope.count(name)) return false;

    Symbol s;
    s.addr = nextAddr++;
    s.kind = SymbolKind::VARIABLE;
    s.uid = nextUid++;
    s.mode = mode;
    s.initialized = initialized;

    scope[name] = s;
    uidMap[s.uid] = &scope[name];   // <<< KLUCZOWE

    return true;
}

bool SymbolTable::declareArray(const std::string& name, long long start, long long end, char mode) {
    auto& scope = scopes.back();
    if (scope.count(name)) return false;

    Symbol s;
    s.addr = nextAddr;
    nextAddr += (end - start + 1);
    s.kind = SymbolKind::ARRAY;
    s.start = start;
    s.end = end;
    s.uid = nextUid++;
    s.mode = mode;

    scope[name] = s;
    uidMap[s.uid] = &scope[name];   // <<< KLUCZOWE

    return true;
}

const Symbol* SymbolTable::lookupByUid(int uid) const {
    auto it = uidMap.find(uid);
    if (it == uidMap.end()) return nullptr;
    return it->second;
}

const Symbol* SymbolTable::lookup(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return &found->second;
        }
    }
    return nullptr;
}

Symbol* SymbolTable::lookupMutable(const std::string& name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) return &found->second;
    }
    return nullptr;
}

std::vector<Symbol>& SymbolTable::getAllSymbols() {
    static std::vector<Symbol> allSymbols;
    allSymbols.clear();
    for (const auto& scope : scopes) {
        for (const auto& [_, sym] : scope) {
            allSymbols.push_back(sym);
        }
    }
    return allSymbols;
}

const std::vector<Symbol> &SymbolTable::getAllSymbols() const
{
    static std::vector<Symbol> allSymbols;
    allSymbols.clear();
    for (const auto& scope : scopes) {
        for (const auto& [_, sym] : scope) {
            allSymbols.push_back(sym);
        }
    }
    return allSymbols;
}

void SymbolTable::dump() const {
    std::cout << "=== SYMBOL TABLE ===\n";
    for (const auto& scope : scopes) {
        for (const auto& [name, sym] : scope) {
            if (sym.kind == SymbolKind::VARIABLE) {
                std::cout << name << " : variable\n";
            } else {
                std::cout << name << " : array ["
                          << sym.start << ":" << sym.end << "]\n";
            }
        }
    }
}
