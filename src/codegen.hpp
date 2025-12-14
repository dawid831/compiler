#pragma once
#include "ast.hpp"
#include "procedure_table.hpp"
#include <iostream>

class CodeGen {
public:
    CodeGen(const ProcedureTable& pt) : proctab(pt) {}

    void genStmt(const Stmt* s);
    void genExpr(const Expr* e);
    void genConst(long long value);
    void emitCondJump(const CondExpr* cond,
                    int labelTrue,
                    int labelFalse);

private:
    const ProcedureTable& proctab;
    int labelCounter = 0;

    int newLabel() { return labelCounter++; }
    void genBinOp(BinOp op);
};
