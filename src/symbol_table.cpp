#include "symbol_table.hpp"

bool SymbolTable::declareVariable(const std::string& name) {
    if (table.count(name)) {
        return false;
    }
    table[name] = { SymbolKind::VARIABLE, 0, 0 };
    return true;
}

bool SymbolTable::declareArray(const std::string& name,
                               long long start,
                               long long end) {
    if (table.count(name)) {
        return false;
    }
    if (start > end) {
        std::cerr << "ERROR: invalid array range\n";
        return false;
    }
    table[name] = { SymbolKind::ARRAY, start, end };
    return true;
}

const Symbol* SymbolTable::lookup(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end()) return nullptr;
    return &it->second;
}

void SymbolTable::dump() const {
    std::cout << "=== SYMBOL TABLE ===\n";
    for (auto& [name, sym] : table) {
        if (sym.kind == SymbolKind::VARIABLE) {
            std::cout << name << " : variable\n";
        } else {
            std::cout << name << " : array [" << sym.start
                      << ":" << sym.end << "]\n";
        }
    }
}
