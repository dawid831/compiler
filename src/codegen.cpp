#include "codegen.hpp"

void CodeGen::genStmt(const Stmt* s) {
    if (!s) return;

    switch (s->kind) {
        case StmtKind::BLOCK: {
            auto b = static_cast<const BlockStmt*>(s);
            for (auto& stmt : b->stmts) {
                genStmt(stmt.get());
            }
            break;
        }
        case StmtKind::ASSIGN: {
            auto a = static_cast<const AssignStmt*>(s);
            genExpr(a->rhs.get());
            std::cout << "STORE " << a->lhs << "\n";
            break;
        }
        case StmtKind::READ: {
            auto r = static_cast<const ReadStmt*>(s);
            std::cout << "READ " << r->name << "\n";
            break;
        }
        case StmtKind::WRITE: {
            auto w = static_cast<const WriteStmt*>(s);
            genExpr(w->expr.get());
            std::cout << "WRITE\n";
            break;
        }
        case StmtKind::CALL: {
            // TODO: implement later
            break;
        }
    }
}

void CodeGen::genExpr(const Expr* e) {
    if (!e) return;

    switch (e->kind) {
        case ExprKind::CONST: {
            auto c = static_cast<const ConstExpr*>(e);
            std::cout << "LOAD_CONST " << c->value << "\n";
            break;
        }
        case ExprKind::VAR: {
            auto v = static_cast<const VarExpr*>(e);
            std::cout << "LOAD " << v->name << "\n";
            break;
        }
        case ExprKind::BINOP: {
            auto b = static_cast<const BinExpr*>(e);

            // klasyczna strategia: postorder
            genExpr(b->left.get());
            genExpr(b->right.get());

            genBinOp(b->op);
            break;
        }
    }
}

void CodeGen::genBinOp(BinOp op) {
    switch (op) {
    case BinOp::ADD: std::cout << "ADD\n"; break;
    case BinOp::SUB: std::cout << "SUB\n"; break;
    case BinOp::MUL: std::cout << "MUL\n"; break;
    case BinOp::DIV: std::cout << "DIV\n"; break;
    case BinOp::MOD: std::cout << "MOD\n"; break;
    }
}
