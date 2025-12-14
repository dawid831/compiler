#include "procedure_table.hpp"

bool ProcedureTable::declareProcedure(const std::string& name,
                                      const std::vector<ProcParam>& params) {
    if (procs.count(name)) return false;
    procs[name] = Procedure{name, params};
    return true;
}

const Procedure* ProcedureTable::lookup(const std::string& name) const {
    auto it = procs.find(name);
    if (it == procs.end()) return nullptr;
    return &it->second;
}
