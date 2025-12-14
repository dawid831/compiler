#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct ProcParam {
    char mode;            // 'I', 'O', 'T'
    std::string name;
};

struct Procedure {
    std::string name;
    std::vector<ProcParam> params;
};

class ProcedureTable {
public:
    bool declareProcedure(const std::string& name,
                          const std::vector<ProcParam>& params);

    const Procedure* lookup(const std::string& name) const;

private:
    std::unordered_map<std::string, Procedure> procs;
};
