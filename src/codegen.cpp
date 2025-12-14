#include "codegen.hpp"

// pamięć programu
std::unordered_map<std::string, int> memory;
int nextAddr = 0;

// pamięć tymczasowa (BEZPIECZNA)
std::unordered_map<std::string, int> tmpMemory;
int nextTmpAddr = 100000;   // DUŻY OFFSET

std::vector<std::unordered_map<std::string,int>> paramEnv;

struct OutCopy {
    int localAddr;
    int callerAddr;
};

int getAddr(const std::string& name) {
    if (!memory.count(name))
        memory[name] = nextAddr++;
    return memory[name];
}

int getTmpAddr(const std::string& name) {
    if (!tmpMemory.count(name))
        tmpMemory[name] = nextTmpAddr++;
    return tmpMemory[name];
}

int resolveAddr(const std::string& name) {
    // Szukamy od najgłębszego (ostatniego) wywołania procedury
    for (int i = (int)paramEnv.size() - 1; i >= 0; --i) {
        auto it = paramEnv[i].find(name);
        if (it != paramEnv[i].end()) {
            return it->second;   // ← adres argumentu
        }
    }
    // Jeśli nie parametr – zwykła zmienna
    return getAddr(name);
}



void CodeGen::flush() {
    for (auto& line : lines) {
        size_t p = 0;
        while ((p = line.find("@L", p)) != std::string::npos) {
            size_t numStart = p + 2;
            size_t numEnd = numStart;

            while (numEnd < line.size() && isdigit((unsigned char)line[numEnd])) {
                numEnd++;
            }

            if (numEnd == numStart) {
                std::cerr << "INTERNAL ERROR: malformed label in: " << line << "\n";
                exit(1);
            }

            int lab = std::stoi(line.substr(numStart, numEnd - numStart));
            auto it = labelPos.find(lab);
            if (it == labelPos.end()) {
                std::cerr << "INTERNAL ERROR: unresolved label " << lab << "\n";
                exit(1);
            }

            line.replace(p, numEnd - p, std::to_string(it->second));
            p += std::to_string(it->second).size();
        }
    }

    for (auto& line : lines) {
        std::cout << line << "\n";
    }
}



void CodeGen::genConst(long long value)
{
    emit("RST a");

    if (value == 0) return;

    // budujemy stałą binarnie (od MSB)
    std::vector<int> bits;
    while (value > 0) {
        bits.push_back(value & 1);
        value >>= 1;
    }

    for (int i = bits.size() - 1; i >= 0; --i) {
        emit("SHL a");
        if (bits[i])
            emit("INC a");
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
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelTrue));
        emit("JUMP @L" + std::to_string(labelFalse));
        break;

    case CondOp::LT:
        // B > A
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelTrue));
        emit("JUMP @L" + std::to_string(labelFalse));
        break;

    case CondOp::GEQ:
        // NOT (A < B)
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelFalse));
        emit("JUMP @L" + std::to_string(labelTrue));
        break;

    case CondOp::LEQ:
        // NOT (A > B)
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelFalse));
        emit("JUMP @L" + std::to_string(labelTrue));
        break;

    case CondOp::EQ:
        // A > B ?
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelFalse));

        // B > A ?
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelFalse));

        emit("JUMP @L" + std::to_string(labelTrue));
        break;

    case CondOp::NEQ:
        // A > B ?
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelTrue));

        // B > A ?
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SWP b");
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelTrue));

        emit("JUMP @L" + std::to_string(labelFalse));
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
            emit("STORE " + std::to_string(resolveAddr(a->lhs)));
            break;
        }
        case StmtKind::READ: {
            auto r = static_cast<const ReadStmt*>(s);
            emit("READ");
            emit("STORE " + std::to_string(resolveAddr(r->name)));
            break;
        }
        case StmtKind::WRITE: {
            auto w = static_cast<const WriteStmt*>(s);
            genExpr(w->expr.get());
            emit("WRITE");
            break;
        }
        case StmtKind::CALL: {
            auto c = static_cast<const CallStmt*>(s);
            const Procedure* proc = proctab.lookup(c->name);

            std::unordered_map<std::string,int> frame;
            std::vector<OutCopy> outCopies;   // ← lokalne

            for (size_t i = 0; i < proc->params.size(); ++i) {
                const auto& param = proc->params[i];
                const std::string& actual = c->args[i];

                if (param.mode == 'I' || param.mode == 'T') {
                    frame[param.name] = resolveAddr(actual);
                }
                else if (param.mode == 'O') {
                    int local = getTmpAddr("__out_" + param.name + "_" + std::to_string(newLabel()));
                    frame[param.name] = local;
                    outCopies.push_back({local, resolveAddr(actual)});
                }
            }

            paramEnv.push_back(std::move(frame));
            genStmt(proc->body);

            for (auto& cpy : outCopies) {
                emit("LOAD "  + std::to_string(cpy.localAddr));
                emit("STORE " + std::to_string(cpy.callerAddr));
            }

            paramEnv.pop_back();
            break;
        }
        case StmtKind::IF: {
            auto i = static_cast<const IfStmt*>(s);

            int thenLabel = newLabel();
            int elseLabel = newLabel();
            int endLabel  = newLabel();

            emitCondJump(i->cond.get(), thenLabel, elseLabel);

            markLabel(thenLabel);
            genStmt(i->thenBranch.get());
            emit("JUMP @L" + std::to_string(endLabel));

            markLabel(elseLabel);
            if (i->elseBranch)
                genStmt(i->elseBranch.get());

            markLabel(endLabel);
            break;
        }
        case StmtKind::WHILE: {
            auto w = static_cast<const WhileStmt*>(s);

            int startLabel = newLabel();
            int bodyLabel  = newLabel();
            int endLabel   = newLabel();

            markLabel(startLabel);
            emitCondJump(w->cond.get(), bodyLabel, endLabel);

            markLabel(bodyLabel);
            genStmt(w->body.get());
            emit("JUMP @L" + std::to_string(startLabel));

            markLabel(endLabel);
            break;
        }
        case StmtKind::REPEAT: {
            auto r = static_cast<const RepeatStmt*>(s);

            int bodyLabel = newLabel();
            int endLabel  = newLabel();

            markLabel(bodyLabel);
            genStmt(r->body.get());
            emitCondJump(r->cond.get(), endLabel, bodyLabel);

            markLabel(endLabel);
            break;
        }
        case StmtKind::FOR: {
            auto f = static_cast<const ForStmt*>(s);

            int startLabel = newLabel();
            int endLabel   = newLabel();
            int skipLabel = newLabel();

            // if (from > to) skip
            if (!f->downto) {
                // from > to ?
                genExpr(f->from.get());
                emit("SWP b");
                genExpr(f->to.get());
                emit("SWP b");
                emit("SUB b");
                emit("JPOS @L" + std::to_string(skipLabel));
            } else {
                // from < to ?
                genExpr(f->to.get());
                emit("SWP b");
                genExpr(f->from.get());
                emit("SWP b");
                emit("SUB b");
                emit("JPOS @L" + std::to_string(skipLabel));
            }

            // iterator = from
            genExpr(f->from.get());
            emit("STORE " + std::to_string(resolveAddr(f->iterator)));

            // licznik iteracji:
            // TO:   cnt = to - from + 1
            // DOWN: cnt = from - to + 1

            if (!f->downto) {
                // to - from
                genExpr(f->to.get());
                emit("SWP b");
                genExpr(f->from.get());
                emit("SWP b");
                emit("SUB b");
            } else {
                // from - to
                genExpr(f->from.get());
                emit("SWP b");
                genExpr(f->to.get());
                emit("SWP b");
                emit("SUB b");
            }

            // +1
            emit("INC a");
            std::string counter = "__for_cnt_" + std::to_string(startLabel);
            emit("STORE " + std::to_string(getTmpAddr(counter)));

            markLabel(startLabel);
            emit("LOAD " + std::to_string(getTmpAddr(counter)));
            emit("JZERO @L" + std::to_string(endLabel));

            // body
            genStmt(f->body.get());

            // iterator ++ / --
            emit("LOAD " + std::to_string(resolveAddr(f->iterator)));
            if (f->downto)
                emit("DEC a");
            else
                emit("INC a");
            emit("STORE " + std::to_string(resolveAddr(f->iterator)));

            // cnt--
            emit("LOAD " + std::to_string(getTmpAddr(counter)));
            emit("DEC a");
            emit("STORE " + std::to_string(getTmpAddr(counter)));

            emit("JUMP @L" + std::to_string(startLabel));
            markLabel(skipLabel);
            markLabel(endLabel);
            break;
        }
        case StmtKind::NOP:
            break;
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
            emit("LOAD " + std::to_string(resolveAddr(v->name)));
            break;
        }
        case ExprKind::BINOP: {
            auto b = static_cast<const BinExpr*>(e);

            genExpr(b->left.get());
            emit("SWP b");
            genExpr(b->right.get());

            switch (b->op) {
                case BinOp::ADD:
                    emit("ADD b");
                    break;
                case BinOp::SUB:
                    emit("SUB b");
                    break;
                case BinOp::MUL: {
                    int loopLabel = newLabel();
                    int skipLabel = newLabel();
                    int endLabel  = newLabel();

                    std::string mulTmp = "__mul_tmp_" + std::to_string(loopLabel);
                    std::string mulRes = "__mul_res_" + std::to_string(loopLabel);

                    // Wejście: po Twoim schemacie
                    // rb = left (po SWP b), ra = right (po genExpr(right))
                    // zapisujemy multiplier (ra) do mulTmp
                    emit("STORE " + std::to_string(getTmpAddr(mulTmp)));

                    // res = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(getTmpAddr(mulRes)));

                    // multiplicand jest w rb (left) – zostawiamy w rb

                    markLabel(loopLabel);

                    // if tmp == 0 -> end
                    emit("LOAD " + std::to_string(getTmpAddr(mulTmp)));
                    emit("JZERO @L" + std::to_string(endLabel));

                    // sprawdź nieparzystość: tmp - 2*(tmp/2)
                    emit("SHR a");
                    emit("SHL a");
                    emit("SWP b"); // b = evenPart, a = multiplicand (było w b)  -> UWAGA: utrzymujemy b jako evenPart
                    emit("LOAD " + std::to_string(getTmpAddr(mulTmp)));
                    emit("SUB b");
                    emit("JZERO @L" + std::to_string(skipLabel));

                    // res += multiplicand (multiplicand trzeba mieć w b)
                    emit("SWP b"); // b = multiplicand, a = (tmp - evenPart)
                    emit("LOAD " + std::to_string(getTmpAddr(mulRes)));
                    emit("ADD b");
                    emit("STORE " + std::to_string(getTmpAddr(mulRes)));

                    markLabel(skipLabel);

                    // multiplicand <<= 1  (b *= 2)
                    emit("LOAD b");
                    emit("SHL a");
                    emit("SWP b");

                    // tmp >>= 1
                    emit("LOAD " + std::to_string(getTmpAddr(mulTmp)));
                    emit("SHR a");
                    emit("STORE " + std::to_string(getTmpAddr(mulTmp)));

                    emit("JUMP @L" + std::to_string(loopLabel));

                    markLabel(endLabel);
                    emit("LOAD " + std::to_string(getTmpAddr(mulRes)));
                    break;
                }
                case BinOp::DIV:
                case BinOp::MOD: {
                    bool isMod = (b->op == BinOp::MOD);

                    int L1      = newLabel(); // find max shift
                    int L2      = newLabel(); // main loop
                    int Lskip   = newLabel(); // skip subtract
                    int Lend    = newLabel(); // end
                    int Ldiv0   = newLabel(); // divisor == 0

                    std::string A = "__div_a_" + std::to_string(L1);
                    std::string B = "__div_b_" + std::to_string(L1);
                    std::string Q = "__div_q_" + std::to_string(L1);
                    std::string C = "__div_c_" + std::to_string(L1); // counter (iterations)

                    // wejście po Twoim schemacie:
                    // rb = left (dividend), ra = right (divisor)

                    // A = dividend
                    emit("SWP b");
                    emit("STORE " + std::to_string(getTmpAddr(A)));

                    // B = divisor
                    emit("SWP b");
                    emit("STORE " + std::to_string(getTmpAddr(B)));

                    // jeśli B == 0 → wynik 0
                    emit("LOAD " + std::to_string(getTmpAddr(B)));
                    emit("JZERO @L" + std::to_string(Ldiv0));

                    // Q = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(getTmpAddr(Q)));

                    // C = 1 (będzie = shifts+1)
                    emit("RST a");
                    emit("INC a");
                    emit("STORE " + std::to_string(getTmpAddr(C)));

                    // ===== L1: przesuwaj B w lewo dopóki (B<<1) <= A =====
                    markLabel(L1);

                    // sprawdź: (B<<1) > A ?
                    // robimy: a = (B<<1) - A i JPOS => stop
                    emit("LOAD " + std::to_string(getTmpAddr(B)));
                    emit("SHL a");                     // a = B<<1
                    emit("SWP b");                     // b = B<<1
                    emit("LOAD " + std::to_string(getTmpAddr(A)));
                    emit("SWP b");                     // b = A, a = B<<1
                    emit("SUB b");                     // a = (B<<1) - A   (ucięte, więc >0 działa)
                    emit("JPOS @L" + std::to_string(L2));

                    // B <<= 1
                    emit("LOAD " + std::to_string(getTmpAddr(B)));
                    emit("SHL a");
                    emit("STORE " + std::to_string(getTmpAddr(B)));

                    // C++  (liczba iteracji pętli 2 rośnie)
                    emit("LOAD " + std::to_string(getTmpAddr(C)));
                    emit("INC a");
                    emit("STORE " + std::to_string(getAddr(C)));

                    emit("JUMP @L" + std::to_string(L1));

                    // ===== L2: main loop (C iteracji) =====
                    markLabel(L2);

                    emit("LOAD " + std::to_string(getTmpAddr(C)));
                    emit("JZERO @L" + std::to_string(Lend));

                    // Q <<= 1
                    emit("LOAD " + std::to_string(getTmpAddr(Q)));
                    emit("SHL a");
                    emit("STORE " + std::to_string(getTmpAddr(Q)));

                    // if A < B => skip subtract
                    // test: (B - A) > 0 ?
                    emit("LOAD " + std::to_string(getTmpAddr(A)));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(getTmpAddr(B)));
                    emit("SUB b");                     // a = B - A
                    emit("JPOS @L" + std::to_string(Lskip));

                    // A -= B
                    emit("LOAD " + std::to_string(getTmpAddr(B)));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(getTmpAddr(A)));
                    emit("SUB b");                     // a = A - B
                    emit("STORE " + std::to_string(getTmpAddr(A)));

                    // Q++
                    emit("LOAD " + std::to_string(getTmpAddr(Q)));
                    emit("INC a");
                    emit("STORE " + std::to_string(getTmpAddr(Q)));

                    markLabel(Lskip);

                    // B >>= 1
                    emit("LOAD " + std::to_string(getTmpAddr(B)));
                    emit("SHR a");
                    emit("STORE " + std::to_string(getTmpAddr(B)));

                    // C--
                    emit("LOAD " + std::to_string(getTmpAddr(C)));
                    emit("DEC a");
                    emit("STORE " + std::to_string(getTmpAddr(C)));

                    emit("JUMP @L" + std::to_string(L2));

                    // divisor==0 → wynik 0
                    markLabel(Ldiv0);
                    emit("RST a");

                    markLabel(Lend);
                    if (isMod) {
                        emit("LOAD " + std::to_string(getTmpAddr(A)));
                    } else {
                        emit("LOAD " + std::to_string(getTmpAddr(Q)));
                    }
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
