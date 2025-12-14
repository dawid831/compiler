#pragma once
#include "ast.hpp"
#include "procedure_table.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class CodeGen {
public:
    CodeGen(const ProcedureTable& pt) : proctab(pt) {}

    void genStmt(const Stmt* s);
    void genExpr(const Expr* e);
    void genConst(long long value);
    void emitCondJump(const CondExpr* cond, int labelTrue, int labelFalse);

    void flush();
    void finish() {
        emit("HALT");
    }
private:
    const ProcedureTable& proctab;
    int labelCounter = 0;

    int newLabel() { return labelCounter++; }

    std::vector<std::string> lines;
    std::unordered_map<int,int> labelPos; // label -> linia (index instrukcji)

    void emit(const std::string& s) { lines.push_back(s); }
    void markLabel(int label) { labelPos[label] = (int)lines.size(); }
};
