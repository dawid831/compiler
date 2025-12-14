#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "ast.hpp"

struct ProcParam {
    char mode;          // 'T', 'I', 'O'
    std::string name;
};

struct Procedure {
    std::string name;
    std::vector<ProcParam> params;
    BlockStmt* body = nullptr;
};

class ProcedureTable {
public:
    bool declareProcedure(const std::string& name,
                          const std::vector<ProcParam>& params);

    void defineBody(const std::string& name, BlockStmt* body);

    const Procedure* lookup(const std::string& name) const;

private:
    std::unordered_map<std::string, Procedure> table;
};
