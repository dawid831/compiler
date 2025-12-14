#include "codegen.hpp"

std::unordered_map<std::string, int> memory;
int nextAddr = 0;

int getAddr(const std::string& name) {
    if (!memory.count(name))
        memory[name] = nextAddr++;
    return memory[name];
}


void CodeGen::genConst(long long value)
{
    std::cout << "RST a\n";

    if (value == 0) return;

    // budujemy stałą binarnie (od MSB)
    std::vector<int> bits;
    while (value > 0) {
        bits.push_back(value & 1);
        value >>= 1;
    }

    for (int i = bits.size() - 1; i >= 0; --i) {
        std::cout << "SHL a\n";
        if (bits[i])
            std::cout << "INC a\n";
    }
}

void CodeGen::emitCondJump(const CondExpr* cond,
                           int labelTrue,
                           int labelFalse)
{
    switch (cond->op) {

    case CondOp::GT:
        // A > B
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelTrue << "\n";
        std::cout << "JUMP " << labelFalse << "\n";
        break;

    case CondOp::LT:
        // B > A
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelTrue << "\n";
        std::cout << "JUMP " << labelFalse << "\n";
        break;

    case CondOp::GEQ:
        // NOT (A < B)
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelFalse << "\n";
        std::cout << "JUMP " << labelTrue << "\n";
        break;

    case CondOp::LEQ:
        // NOT (A > B)
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelFalse << "\n";
        std::cout << "JUMP " << labelTrue << "\n";
        break;

    case CondOp::EQ:
        // A > B ?
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelFalse << "\n";

        // B > A ?
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelFalse << "\n";

        std::cout << "JUMP " << labelTrue << "\n";
        break;

    case CondOp::NEQ:
        // A > B ?
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelTrue << "\n";

        // B > A ?
        genExpr(cond->right.get());
        std::cout << "SWP b\n";
        genExpr(cond->left.get());
        std::cout << "SWP b\n";
        std::cout << "SUB b\n";
        std::cout << "JPOS " << labelTrue << "\n";

        std::cout << "JUMP " << labelFalse << "\n";
        break;
    }
}


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
            std::cout << "STORE " << getAddr(a->lhs) << "\n";
            break;
        }
        case StmtKind::READ: {
            auto r = static_cast<const ReadStmt*>(s);
            std::cout << "READ " << getAddr(r->name) << "\n";
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

            int thenLabel = newLabel();
            int elseLabel = newLabel();
            int endLabel  = newLabel();

            emitCondJump(i->cond.get(), thenLabel, elseLabel);

            std::cout << thenLabel << ":\n";
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
            int bodyLabel  = newLabel();
            int endLabel   = newLabel();

            std::cout << startLabel << ":\n";
            emitCondJump(w->cond.get(), bodyLabel, endLabel);

            std::cout << bodyLabel << ":\n";
            genStmt(w->body.get());
            std::cout << "JUMP " << startLabel << "\n";

            std::cout << endLabel << ":\n";
            break;
        }
        case StmtKind::REPEAT: {
            auto r = static_cast<const RepeatStmt*>(s);

            int bodyLabel = newLabel();
            int endLabel  = newLabel();

            std::cout << bodyLabel << ":\n";
            genStmt(r->body.get());
            emitCondJump(r->cond.get(), endLabel, bodyLabel);

            std::cout << endLabel << ":\n";
            break;
        }
        case StmtKind::FOR: {
            auto f = static_cast<const ForStmt*>(s);

            int startLabel = newLabel();
            int bodyLabel  = newLabel();
            int endLabel   = newLabel();
            int skipLabel = newLabel();

            // if (from > to) skip
            if (!f->downto) {
                // from > to ?
                genExpr(f->from.get());
                std::cout << "SWP b\n";
                genExpr(f->to.get());
                std::cout << "SWP b\n";
                std::cout << "SUB b\n";
                std::cout << "JPOS " << skipLabel << "\n";
            } else {
                // from < to ?
                genExpr(f->to.get());
                std::cout << "SWP b\n";
                genExpr(f->from.get());
                std::cout << "SWP b\n";
                std::cout << "SUB b\n";
                std::cout << "JPOS " << skipLabel << "\n";
            }

            // iterator = from
            genExpr(f->from.get());
            std::cout << "STORE " << getAddr(f->iterator) << "\n";

            // licznik iteracji:
            // TO:   cnt = to - from + 1
            // DOWN: cnt = from - to + 1

            if (!f->downto) {
                // to - from
                genExpr(f->to.get());
                std::cout << "SWP b\n";
                genExpr(f->from.get());
                std::cout << "SWP b\n";
                std::cout << "SUB b\n";
            } else {
                // from - to
                genExpr(f->from.get());
                std::cout << "SWP b\n";
                genExpr(f->to.get());
                std::cout << "SWP b\n";
                std::cout << "SUB b\n";
            }

            // +1
            std::cout << "INC a\n";
            std::string counter = "__for_cnt_" + std::to_string(startLabel);
            std::cout << "STORE " << getAddr(counter) << "\n";

            std::cout << startLabel << ":\n";
            std::cout << "LOAD " << getAddr(counter) << "\n";
            std::cout << "JZERO " << endLabel << "\n";

            // body
            genStmt(f->body.get());

            // iterator ++ / --
            std::cout << "LOAD " << getAddr(f->iterator) << "\n";
            if (f->downto)
                std::cout << "DEC a\n";
            else
                std::cout << "INC a\n";
            std::cout << "STORE " << getAddr(f->iterator) << "\n";

            // cnt--
            std::cout << "LOAD " << getAddr(counter) << "\n";
            std::cout << "DEC a\n";
            std::cout << "STORE " << getAddr(counter) << "\n";

            std::cout << "JUMP " << startLabel << "\n";
            std::cout << endLabel << ":\n";
            std::cout << skipLabel << ":\n";
            break;
        }
    }
}

void CodeGen::genExpr(const Expr* e) {
    if (!e) return;

    switch (e->kind) {
        case ExprKind::CONST: {
            auto c = static_cast<const ConstExpr*>(e);
            genConst(c->value);
            break;
        }
        case ExprKind::VAR: {
            auto v = static_cast<const VarExpr*>(e);
            std::cout << "LOAD " << getAddr(v->name) << "\n";
            break;
        }
        case ExprKind::BINOP: {
            auto b = static_cast<const BinExpr*>(e);

            genExpr(b->left.get());
            std::cout << "SWP b\n";
            genExpr(b->right.get());

            switch (b->op) {
                case BinOp::ADD:
                    std::cout << "ADD b\n";
                    break;
                case BinOp::SUB:
                    std::cout << "SUB b\n";
                    break;
                case BinOp::MUL: {
                    int loopLabel = newLabel();
                    int endLabel  = newLabel();

                    // ra = right, rb = left
                    // result = 0
                    std::cout << "RST a\n";        // ra = 0
                    std::cout << "SWP b\n";        // rb = 0, ra = left
                    std::cout << "SWP b\n";        // rb = left, ra = 0

                    // teraz:
                    // rb = multiplicand (a)
                    // ra = result (0)
                    // potrzebujemy jeszcze multiplier → przechowamy go w pamięci tymczasowej

                    std::string mulTmp = "__mul_tmp_" + std::to_string(loopLabel);
                    std::string mulRes = "__mul_res_" + std::to_string(loopLabel);

                    // zapisz multiplier (right)
                    std::cout << "STORE " << getAddr(mulTmp) << "\n";
                    std::cout << "STORE " << getAddr(mulRes) << "\n"; // result = 0

                    std::cout << loopLabel << ":\n";

                    // load multiplier
                    std::cout << "LOAD " << getAddr(mulTmp) << "\n";
                    std::cout << "JZERO " << endLabel << "\n";

                    // if (multiplier % 2 == 1)
                    std::cout << "SHR a\n";        // ra = multiplier / 2
                    std::cout << "SHL a\n";        // ra = (multiplier / 2) * 2
                    std::cout << "LOAD " << getAddr(mulTmp) << "\n";
                    std::cout << "SUB b\n";        // ra = multiplier - even_part
                    std::cout << "JZERO " << loopLabel << "_skip\n";

                    // result += multiplicand
                    std::cout << "LOAD " << getAddr(mulRes) << "\n";
                    std::cout << "ADD b\n";
                    std::cout << "STORE " << getAddr(mulRes) << "\n";

                    std::cout << loopLabel << "_skip:\n";

                    // multiplicand <<= 1
                    std::cout << "LOAD b\n";
                    std::cout << "SHL a\n";
                    std::cout << "SWP b\n";

                    // multiplier >>= 1
                    std::cout << "LOAD " << getAddr(mulTmp) << "\n";
                    std::cout << "SHR a\n";
                    std::cout << "STORE " << getAddr(mulTmp) << "\n";

                    std::cout << "JUMP " << loopLabel << "\n";

                    std::cout << endLabel << ":\n";
                    std::cout << "LOAD " << getAddr(mulRes) << "\n";
                    break;
                }
                case BinOp::DIV:
                case BinOp::MOD: {
                    bool isMod = (b->op == BinOp::MOD);

                    int loop1 = newLabel();
                    int loop2 = newLabel();
                    int end   = newLabel();

                    std::string A = "__div_a_" + std::to_string(loop1);
                    std::string B = "__div_b_" + std::to_string(loop1);
                    std::string Q = "__div_q_" + std::to_string(loop1);
                    std::string S = "__div_sh_" + std::to_string(loop1);

                    // start: ra = divisor, rb = dividend
                    // save A = dividend
                    std::cout << "SWP b\n";           // ra = dividend
                    std::cout << "STORE " << getAddr(A) << "\n";

                    // save B = divisor
                    std::cout << "SWP b\n";           // ra = divisor
                    std::cout << "STORE " << getAddr(B) << "\n";

                    // Q = 0, shift = 0
                    std::cout << "RST a\n";
                    std::cout << "STORE " << getAddr(Q) << "\n";
                    std::cout << "STORE " << getAddr(S) << "\n";

                    // === first loop: find max shift ===
                    std::cout << loop1 << ":\n";
                    std::cout << "LOAD " << getAddr(B) << "\n";
                    std::cout << "SHL a\n";
                    std::cout << "SWP b\n";
                    std::cout << "LOAD " << getAddr(A) << "\n";
                    std::cout << "SUB b\n";
                    std::cout << "JPOS " << loop2 << "\n";

                    // B <<= 1, shift++
                    std::cout << "LOAD " << getAddr(B) << "\n";
                    std::cout << "SHL a\n";
                    std::cout << "STORE " << getAddr(B) << "\n";

                    std::cout << "LOAD " << getAddr(S) << "\n";
                    std::cout << "INC a\n";
                    std::cout << "STORE " << getAddr(S) << "\n";

                    std::cout << "JUMP " << loop1 << "\n";

                    // === second loop: subtract & build quotient ===
                    std::cout << loop2 << ":\n";
                    std::cout << "LOAD " << getAddr(S) << "\n";
                    std::cout << "JZERO " << end << "\n";

                    std::cout << "LOAD " << getAddr(A) << "\n";
                    std::cout << "SWP b\n";
                    std::cout << "LOAD " << getAddr(B) << "\n";
                    std::cout << "SUB b\n";
                    std::cout << "JPOS " << loop2 << "_skip\n";

                    // A -= B
                    std::cout << "STORE " << getAddr(A) << "\n";

                    // Q += (1 << shift)
                    std::cout << "LOAD " << getAddr(Q) << "\n";
                    std::cout << "INC a\n";
                    std::cout << "STORE " << getAddr(Q) << "\n";

                    std::cout << loop2 << "_skip:\n";

                    // B >>= 1, shift--
                    std::cout << "LOAD " << getAddr(B) << "\n";
                    std::cout << "SHR a\n";
                    std::cout << "STORE " << getAddr(B) << "\n";

                    std::cout << "LOAD " << getAddr(S) << "\n";
                    std::cout << "DEC a\n";
                    std::cout << "STORE " << getAddr(S) << "\n";

                    std::cout << "JUMP " << loop2 << "\n";

                    std::cout << end << ":\n";
                    if (isMod)
                        std::cout << "LOAD " << getAddr(A) << "\n";
                    else
                        std::cout << "LOAD " << getAddr(Q) << "\n";
                    break;
                }

                default:
                    std::cerr << "BINOP not implemented yet\n";
                    exit(1);
            }
            break;
        }
    }
}
