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
            auto c = static_cast<const CallStmt*>(s);

            const Procedure* proc = proctab.lookup(c->name);
            if (!proc || !proc->body) {
                std::cerr << "INTERNAL ERROR: procedure body missing\n";
                exit(1);
            }

            // INLINE: generujemy ciało procedury
            genStmt(proc->body);

            break;
        }
        case StmtKind::IF: {
            auto i = static_cast<const IfStmt*>(s);

            int elseLabel = newLabel();
            int endLabel  = newLabel();

            genExpr(i->cond.get());
            std::cout << "JZERO " << elseLabel << "\n";

            genStmt(i->thenBranch.get());
            std::cout << "JUMP " << endLabel << "\n";

            std::cout << elseLabel << ":\n";
            if (i->elseBranch)
                genStmt(i->elseBranch.get());

            std::cout << endLabel << ":\n";
            break;
        }
        case StmtKind::WHILE: {
            auto w = static_cast<const WhileStmt*>(s);

            int startLabel = newLabel();
            int endLabel   = newLabel();

            std::cout << startLabel << ":\n";
            genExpr(w->cond.get());
            std::cout << "JZERO " << endLabel << "\n";

            genStmt(w->body.get());
            std::cout << "JUMP " << startLabel << "\n";

            std::cout << endLabel << ":\n";
            break;
        }
        case StmtKind::REPEAT: {
            auto r = static_cast<const RepeatStmt*>(s);

            int startLabel = newLabel();

            std::cout << startLabel << ":\n";
            genStmt(r->body.get());
            genExpr(r->cond.get());
            std::cout << "JZERO " << startLabel << "\n";
            break;
        }
        case StmtKind::NOP: {
            // Nic nie robimy
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
