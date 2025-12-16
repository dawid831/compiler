#include "codegen.hpp"
#include "symbol_table.hpp"

extern SymbolTable symtab;

// pamięć programu
std::unordered_map<int, int> memory;
int nextAddr = 0;

// pamięć tymczasowa (BEZPIECZNA)
std::unordered_map<std::string, int> tmpMemory;
int nextTmpAddr = 100000;   // DUŻY OFFSET

std::vector<std::unordered_map<int,int>> paramEnv;

int getAddr(const VarExpr* v) {
    auto it = memory.find(v->uid);
    if (it != memory.end()) return it->second;

    if (v->isArray) {
        int base = nextAddr;
        long long len = v->arrEnd - v->arrStart + 1;
        memory[v->uid] = base;
        nextAddr += (int)len;
        return base;
    }

    memory[v->uid] = nextAddr++;
    return memory[v->uid];
}

int getTmpAddr(const std::string& name) {
    if (!tmpMemory.count(name))
        tmpMemory[name] = nextTmpAddr++;
    return tmpMemory[name];
}

int resolveAddr(const VarExpr* v) {
    for (int i = (int)paramEnv.size() - 1; i >= 0; --i) {
        auto it = paramEnv[i].find(v->uid);
        if (it != paramEnv[i].end())
            return it->second;
    }
    return getAddr(v);
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

void CodeGen::emitArrayAddrToC(const VarExpr* arr) {
    // arr->index MUST exist
    genExpr(arr->index.get());       // a = index

    // a = index - start
    emit("SWP b");                   // b = index
    genConst(arr->arrStart);         // a = start
    emit("SWP b");                   // b = start, a = index
    emit("SUB b");                   // a = index - start

    // a = base + (index-start)
    emit("SWP b");                   // b = offset
    genConst(getAddr(arr));          // a = base
    emit("ADD b");                   // a = base + offset

    emit("SWP c");                   // rc = address
}

int resolveAddrByUid(int uid) {
    for (int i = paramEnv.size() - 1; i >= 0; --i) {
        auto it = paramEnv[i].find(uid);
        if (it != paramEnv[i].end()) return it->second;
    }
    return memory[uid];
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
            if (!a->lhs->index) {
                emit("STORE " + std::to_string(resolveAddr(a->lhs.get())));
            } else {
                int tmp = getTmpAddr("__assign_rhs_" + std::to_string(newLabel()));
                emit("STORE " + std::to_string(tmp));

                emitArrayAddrToC(a->lhs.get());

                emit("LOAD " + std::to_string(tmp));
                emit("RSTORE c");
            }
            break;
        }
        case StmtKind::READ: {
            auto r = static_cast<const ReadStmt*>(s);
            emit("READ");
            if (!r->target->index) {
                emit("STORE " + std::to_string(resolveAddr(r->target.get())));
            } else {
                int tmp = getTmpAddr("__read_tmp_" + std::to_string(newLabel()));
                emit("STORE " + std::to_string(tmp));

                emitArrayAddrToC(r->target.get());

                emit("LOAD " + std::to_string(tmp));
                emit("RSTORE c");
            }
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

            if (!proc || !proc->body) {
                std::cerr << "INTERNAL ERROR: procedure body missing\n";
                exit(1);
            }

            if (proc->params.size() != c->args.size()) {
                std::cerr << "INTERNAL ERROR: arg count mismatch in call to " << c->name << "\n";
                exit(1);
            }

            struct OutCopy {
                int localAddr;
                int callerAddr;
            };

            std::vector<OutCopy> outCopies;   // ← LOKALNE, tylko dla tego CALL

            std::unordered_map<int,int> frame;
            frame.reserve(proc->params.size());
            for (size_t i = 0; i < proc->params.size(); ++i) {
                const ProcParam& param = proc->params[i];
                const std::string& actualName = c->args[i];
                const Symbol* s = symtab.lookup(actualName);
                if (!s) {
                    std::cerr << "INTERNAL ERROR: unknown argument " << actualName << "\n";
                    exit(1);
                }
                int actualUid = s->uid;

                VarExpr tmp(actualName, actualUid);
                int actualAddr = resolveAddr(&tmp);

                if (param.mode == 'I' || param.mode == 'T') {
                    frame[param.uid] = actualAddr;
                } else if (param.mode == 'O') {
                    int local = getTmpAddr("__out_" + std::to_string(param.uid) + "_" + std::to_string(newLabel()));
                    frame[param.uid] = local;
                    outCopies.push_back({ local, actualAddr });
                } else {
                    std::cerr << "INTERNAL ERROR: unknown param mode\n";
                    exit(1);
                }
            }


            // wejście w procedurę
            paramEnv.push_back(std::move(frame));
            genStmt(proc->body);
            paramEnv.pop_back();

            // kopiowanie parametrów OUT
            for (const auto& cpy : outCopies) {
                emit("LOAD "  + std::to_string(cpy.localAddr));
                emit("STORE " + std::to_string(cpy.callerAddr));
            }

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
            VarExpr it(f->iterator, f->iteratorUid);
            int itAddr = resolveAddr(&it);

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
            emit("STORE " + std::to_string(itAddr));

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
            emit("LOAD " + std::to_string(itAddr));
            if (f->downto)
                emit("DEC a");
            else
                emit("INC a");
            emit("STORE " + std::to_string(itAddr));

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

            if (!v->index) {
                emit("LOAD " + std::to_string(resolveAddr(v)));
            } else {
                emitArrayAddrToC(v);
                emit("RLOAD c");
            }
            break;
        }
        case ExprKind::BINOP: {
            auto b = static_cast<const BinExpr*>(e);

                if (b->op == BinOp::SUB) {
                    // chcemy: left - right
                    genExpr(b->right.get());   // a = right
                    emit("SWP b");             // b = right
                    genExpr(b->left.get());    // a = left
                    emit("SUB b");             // a = left - right
                    break;
                }

            genExpr(b->left.get());
            emit("SWP b");
            genExpr(b->right.get());

            switch (b->op) {
                case BinOp::ADD:
                    emit("ADD b");
                    break;
                case BinOp::MUL: {
                    // Logarytmiczna multiplikacja (Russian peasant / shift-add)
                    // Wejście po schemacie genExpr(left); SWP b; genExpr(right):
                    //   b = left  (multiplicand)
                    //   a = right (multiplier)
                    int Lloop = newLabel();
                    int Lskip = newLabel();
                    int Lend  = newLabel();

                    std::string mulA    = "__mul_a_" + std::to_string(Lloop); // multiplicand
                    std::string mulB    = "__mul_b_" + std::to_string(Lloop); // multiplier
                    std::string mulRes  = "__mul_r_" + std::to_string(Lloop); // result
                    std::string mulEven = "__mul_e_" + std::to_string(Lloop); // 2*(mulB/2)

                    // mulA = left (z rejestru b)
                    emit("SWP b");
                    emit("STORE " + std::to_string(getTmpAddr(mulA)));
                    // mulB = right (z rejestru a)
                    emit("SWP b");
                    emit("STORE " + std::to_string(getTmpAddr(mulB)));

                    // res = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(getTmpAddr(mulRes)));

                    markLabel(Lloop);

                    // if mulB == 0 -> end
                    emit("LOAD " + std::to_string(getTmpAddr(mulB)));
                    emit("JZERO @L" + std::to_string(Lend));

                    // mulEven = 2*(mulB/2)
                    emit("LOAD " + std::to_string(getTmpAddr(mulB)));
                    emit("SHR a");
                    emit("SHL a");
                    emit("STORE " + std::to_string(getTmpAddr(mulEven)));

                    // if mulB - mulEven == 0 then even -> skip add
                    emit("LOAD " + std::to_string(getTmpAddr(mulEven)));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(getTmpAddr(mulB)));
                    emit("SUB b");
                    emit("JZERO @L" + std::to_string(Lskip));

                    // res += mulA
                    emit("LOAD " + std::to_string(getTmpAddr(mulA)));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(getTmpAddr(mulRes)));
                    emit("ADD b");
                    emit("STORE " + std::to_string(getTmpAddr(mulRes)));

                    markLabel(Lskip);

                    // mulA <<= 1
                    emit("LOAD " + std::to_string(getTmpAddr(mulA)));
                    emit("SHL a");
                    emit("STORE " + std::to_string(getTmpAddr(mulA)));

                    // mulB >>= 1
                    emit("LOAD " + std::to_string(getTmpAddr(mulB)));
                    emit("SHR a");
                    emit("STORE " + std::to_string(getTmpAddr(mulB)));

                    emit("JUMP @L" + std::to_string(Lloop));

                    markLabel(Lend);
                    emit("LOAD " + std::to_string(getTmpAddr(mulRes)));
                    break;
                }
                case BinOp::DIV:
                case BinOp::MOD: {
                    bool isMod = (b->op == BinOp::MOD);

                    int L1    = newLabel(); // find max shift
                    int L2    = newLabel(); // main loop
                    int Lskip = newLabel(); // skip subtract
                    int Lend  = newLabel(); // end
                    int Ldiv0 = newLabel(); // divisor == 0

                    std::string A = "__div_a_" + std::to_string(L1);
                    std::string B = "__div_b_" + std::to_string(L1);
                    std::string Q = "__div_q_" + std::to_string(L1);
                    std::string C = "__div_c_" + std::to_string(L1); // counter = shifts+1

                    auto aA = [&]{ return getTmpAddr(A); };
                    auto aB = [&]{ return getTmpAddr(B); };
                    auto aQ = [&]{ return getTmpAddr(Q); };
                    auto aC = [&]{ return getTmpAddr(C); };

                    // wejście: rb = dividend (left), ra = divisor (right)

                    // A = dividend
                    emit("SWP b");
                    emit("STORE " + std::to_string(aA()));

                    // B = divisor
                    emit("SWP b");
                    emit("STORE " + std::to_string(aB()));

                    // if B == 0 -> 0
                    emit("LOAD " + std::to_string(aB()));
                    emit("JZERO @L" + std::to_string(Ldiv0));

                    // Q = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(aQ()));

                    // C = 1
                    emit("RST a");
                    emit("INC a");
                    emit("STORE " + std::to_string(aC()));

                    // ===== L1: while ((B<<1) <= A) { B<<=1; C++; } =====
                    markLabel(L1);

                    // a = (B<<1) - A ; if >0 stop
                    emit("LOAD " + std::to_string(aB()));
                    emit("SHL a");                 // a = B<<1
                    emit("SWP b");                 // b = B<<1
                    emit("LOAD " + std::to_string(aA()));
                    emit("SWP b");                 // b = A, a = B<<1
                    emit("SUB b");                 // a = (B<<1) - A
                    emit("JPOS @L" + std::to_string(L2));

                    // B <<= 1
                    emit("LOAD " + std::to_string(aB()));
                    emit("SHL a");
                    emit("STORE " + std::to_string(aB()));

                    // C++
                    emit("LOAD " + std::to_string(aC()));
                    emit("INC a");
                    emit("STORE " + std::to_string(aC()));

                    emit("JUMP @L" + std::to_string(L1));

                    // ===== L2: repeat C times =====
                    markLabel(L2);

                    emit("LOAD " + std::to_string(aC()));
                    emit("JZERO @L" + std::to_string(Lend));

                    // Q <<= 1
                    emit("LOAD " + std::to_string(aQ()));
                    emit("SHL a");
                    emit("STORE " + std::to_string(aQ()));

                    // if (A < B) skip
                    // test: (B - A) > 0 ?
                    emit("LOAD " + std::to_string(aA()));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(aB()));
                    emit("SUB b");                 // a = B - A
                    emit("JPOS @L" + std::to_string(Lskip));

                    // A -= B
                    emit("LOAD " + std::to_string(aB()));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(aA()));
                    emit("SUB b");                 // a = A - B
                    emit("STORE " + std::to_string(aA()));

                    // Q++
                    emit("LOAD " + std::to_string(aQ()));
                    emit("INC a");
                    emit("STORE " + std::to_string(aQ()));

                    markLabel(Lskip);

                    // B >>= 1
                    emit("LOAD " + std::to_string(aB()));
                    emit("SHR a");
                    emit("STORE " + std::to_string(aB()));

                    // C--
                    emit("LOAD " + std::to_string(aC()));
                    emit("DEC a");
                    emit("STORE " + std::to_string(aC()));

                    emit("JUMP @L" + std::to_string(L2));

                    // divisor==0 -> 0
                    markLabel(Ldiv0);
                    emit("RST a");
                    emit("JUMP @L" + std::to_string(Lend));

                    markLabel(Lend);
                    if (isMod) emit("LOAD " + std::to_string(aA()));
                    else       emit("LOAD " + std::to_string(aQ()));
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
