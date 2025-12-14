#include "ast_print.hpp"

void printExpr(const Expr* e, int indentLvl) {
    if (!e) return;

    indent(indentLvl);

    switch (e->kind) {
        case ExprKind::CONST: {
            auto c = static_cast<const ConstExpr*>(e);
            std::cout << "CONST " << c->value << "\n";
            break;
        }
        case ExprKind::VAR: {
            auto v = static_cast<const VarExpr*>(e);
            std::cout << "VAR " << v->name << "\n";
            break;
        }
        case ExprKind::BINOP: {
            auto b = static_cast<const BinExpr*>(e);
            std::cout << "BINOP ";
            switch (b->op) {
                case BinOp::ADD: std::cout << "+\n"; break;
                case BinOp::SUB: std::cout << "-\n"; break;
                case BinOp::MUL: std::cout << "*\n"; break;
                case BinOp::DIV: std::cout << "/\n"; break;
                case BinOp::MOD: std::cout << "%\n"; break;
            }
            printExpr(b->left.get(), indentLvl + 1);
            printExpr(b->right.get(), indentLvl + 1);
            break;
        }
    }
}

void printStmt(const Stmt* s, int indentLvl) {
    if (!s) return;

    indent(indentLvl);

    switch (s->kind) {
        case StmtKind::ASSIGN: {
            auto a = static_cast<const AssignStmt*>(s);
            std::cout << "ASSIGN " << a->lhs << "\n";
            printExpr(a->rhs.get(), indentLvl + 1);
            break;
        }
        case StmtKind::READ: {
            auto r = static_cast<const ReadStmt*>(s);
            std::cout << "READ " << r->name << "\n";
            break;
        }
        case StmtKind::WRITE: {
            auto w = static_cast<const WriteStmt*>(s);
            std::cout << "WRITE\n";
            printExpr(w->expr.get(), indentLvl + 1);
            break;
        }
        case StmtKind::CALL: {
            auto c = static_cast<const CallStmt*>(s);
            std::cout << "CALL " << c->name << "\n";
            break;
        }
        default:
            break;
    }
}
