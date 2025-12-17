#include "symbol_table.hpp"
#include <unordered_set>

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
    s.kind = SymbolKind::VARIABLE;
    s.uid = nextUid++;
    s.mode = mode;
    s.initialized = initialized;

    scope[name] = s;
    uidMap[s.uid] = scope[name];

    return true;
}

bool SymbolTable::declareArray(const std::string& name, long long start, long long end, char mode) {
    auto& scope = scopes.back();
    if (scope.count(name)) return false;

    Symbol s;
    s.kind = SymbolKind::ARRAY;
    s.start = start;
    s.end = end;
    s.uid = nextUid++;
    s.mode = mode;

    scope[name] = s;
    uidMap[s.uid] = scope[name];

    return true;
}

void SymbolTable::dumpNamesUidsAddrs() const {
    std::cout << "=== SYMBOLS (name -> uid -> addr) ===\n";

    std::unordered_set<int> seenUid;

    // idziemy od zewnętrznego do wewnętrznego albo odwrotnie – tu od wewnętrznego,
    // żeby było widać shadowing; a seenUid nie dubluje uidów.
    for (auto sit = scopes.rbegin(); sit != scopes.rend(); ++sit) {
        for (const auto& [name, symInScope] : *sit) {
            int uid = symInScope.uid;
            if (seenUid.count(uid)) continue;
            seenUid.insert(uid);

            const Symbol* real = lookupByUid(uid); // addr z uidMap
            int addr = real ? real->addr : -999;

            std::cout << name
                      << "  uid=" << uid
                      << "  addr=" << addr
                      << "  kind=" << (symInScope.kind == SymbolKind::ARRAY ? "ARRAY" : "VAR");

            if (symInScope.kind == SymbolKind::ARRAY) {
                std::cout << " [" << symInScope.start << ":" << symInScope.end << "]";
            }

            std::cout << "  mode=" << symInScope.mode
                      << "\n";
        }
    }

    std::cout << "====================================\n";
}

const Symbol* SymbolTable::lookupByUid(int uid) const {
    auto it = uidMap.find(uid);
    if (it == uidMap.end()) return nullptr;
    return &it->second;
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
