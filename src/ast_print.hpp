#pragma once
#include "ast.hpp"
#include <iostream>

void printExpr(const Expr* e, int indent = 0);
void printStmt(const Stmt* s, int indent = 0);

inline void indent(int n) {
    for (int i = 0; i < n; ++i) std::cout << "  ";
}