#pragma once
#include "ast.hpp"
#include <iostream>

class CodeGen {
public:
    void genStmt(const Stmt* s);
    void genExpr(const Expr* e);

private:
    void genBinOp(BinOp op);
};
