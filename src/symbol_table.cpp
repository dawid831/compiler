#include "symbol_table.hpp"

void SymbolTable::enterScope() {
    scopes.emplace_back();
}

void SymbolTable::leaveScope() {
    if (!scopes.empty())
        scopes.pop_back();
}

bool SymbolTable::declareVariable(const std::string& name) {
    auto& current = scopes.back();
    if (current.count(name)) {
        return false;
    }
    current[name] = { SymbolKind::VARIABLE, 0, 0 };
    return true;
}

bool SymbolTable::declareArray(const std::string& name,
                               long long start,
                               long long end) {
    auto& current = scopes.back();
    if (current.count(name)) {
        return false;
    }
    if (start > end) {
        std::cerr << "ERROR: invalid array range\n";
        return false;
    }
    current[name] = { SymbolKind::ARRAY, start, end };
    return true;
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
