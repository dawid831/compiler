#include "procedure_table.hpp"

bool ProcedureTable::declareProcedure(const std::string& name,
                                      const std::vector<ProcParam>& params) {
    if (table.count(name)) return false;
    table[name] = {name, params, nullptr};
    return true;
}

void ProcedureTable::defineBody(const std::string& name, BlockStmt* body) {
    table[name].body = body;
}

const Procedure* ProcedureTable::lookup(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end()) return nullptr;
    return &it->second;
}
