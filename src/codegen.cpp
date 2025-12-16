#include "codegen.hpp"
#include "symbol_table.hpp"

extern SymbolTable symtab;

struct ParamBinding {
    int addr = -1;          // adres bazowy (dla tablic) albo adres zmiennej
    bool isArray = false;
    long long arrStart = 0;
    long long arrEnd = 0;
};

std::vector<std::unordered_map<int, ParamBinding>> paramEnv;

int nextAddr = 0;

void CodeGen::allocateAllSymbols() {
    for (Symbol& s : symtab.getAllSymbols()) {
        if (s.addr != -1) continue;

        s.addr = nextAddr;

        if (s.kind == SymbolKind::ARRAY) {
            nextAddr += (s.end - s.start + 1);
        } else {
            nextAddr += 1;
        }
    }
}

int getTmpAddr(const std::string&) {
    return nextAddr++;
}

int resolveAddr(const VarExpr* v) {
    // 1. parametry / iteratory FOR
    for (auto it = paramEnv.rbegin(); it != paramEnv.rend(); ++it)
        if (it->count(v->uid))
            return (*it)[v->uid].addr;

    // 2. zwykła zmienna
    const Symbol* s = symtab.lookupByUid(v->uid);
    if (!s || s->addr < 0) {
        std::cerr << "INTERNAL ERROR: unresolved variable addr\n";
        exit(1);
    }
    return s->addr;
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

    case CondOp::EQ:
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SWP b");
        emit("SUB b");               // left - right
        emit("JZERO @L" + std::to_string(labelTrue));
        emit("JUMP  @L" + std::to_string(labelFalse));
        break;

    case CondOp::NEQ:
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SWP b");
        emit("SUB b");
        emit("JZERO @L" + std::to_string(labelFalse));
        emit("JUMP  @L" + std::to_string(labelTrue));
        break;

    case CondOp::LT:
        // left < right  ⇔  right - left > 0
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SUB b");               // right - left
        emit("JZERO @L" + std::to_string(labelFalse));
        emit("JUMP  @L" + std::to_string(labelTrue));
        break;

    case CondOp::LEQ:
        // left <= right ⇔ right - left >= 0 (zawsze prawda poza przepełnieniem)
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SUB b");
        emit("JUMP @L" + std::to_string(labelTrue));
        break;

    case CondOp::GT:
        // left > right ⇔ left - right > 0
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SUB b");
        emit("JZERO @L" + std::to_string(labelFalse));
        emit("JUMP  @L" + std::to_string(labelTrue));
        break;

    case CondOp::GEQ:
        // left >= right ⇔ left - right >= 0 (zawsze prawda poza 0)
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SUB b");
        emit("JUMP @L" + std::to_string(labelTrue));
        break;
    }
}


int getForCounterAddr() {
    static int forBase = 100000; // albo > max symboli
    return forBase++;
}

void CodeGen::emitArrayAddrToC(const VarExpr* arr) {
    // arr->index MUST exist
    genExpr(arr->index.get());       // a = index

    // Jeżeli to parametr tablicowy (T), to w czasie generowania (inline'owanie)
    // znamy faktyczny zakres tablicy przekazanej w wywołaniu.
    long long start = arr->arrStart;
    for (size_t i = paramEnv.size(); i-- > 0; ) {
        auto it = paramEnv[i].find(arr->uid);
        if (it != paramEnv[i].end() && it->second.isArray) {
            start = it->second.arrStart;
            break;
        }
    }

    // a = index - start
    emit("SWP b");                   // b = index
    genConst(start);                 // a = start
    emit("SWP b");                   // b = start, a = index
    emit("SUB b");                   // a = index - start

    // a = base + (index-start)
    emit("SWP b");                   // b = offset
    genConst(resolveAddr(arr));      // a = base (z mapowania parametrów albo z pamięci globalnej)
    emit("ADD b");                   // a = base + offset

    emit("SWP c");                   // rc = address
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

            std::unordered_map<int, ParamBinding> frame;
            frame.reserve(proc->params.size());
            for (size_t i = 0; i < proc->params.size(); ++i) {
                const ProcParam& param = proc->params[i];
                const CallArg& actualName = c->args[i];
                if (!s) {
                    //std::cerr << "INTERNAL ERROR: unknown argument " << actualName << "\n";
                    exit(1);
                }
                int actualUid = actualName.uid;
                int actualAddr = symtab.lookupByUid(actualUid)->addr;

                ParamBinding bind;
                bind.addr = actualAddr;

                if (param.mode == 'T') {
                    bind.isArray = true;
                    bind.arrStart = actualName.start;
                    bind.arrEnd   = actualName.end;
                    frame[param.uid] = bind;
                } else if (param.mode == ' ') {
                    // domyślny parametr → IN-OUT (przez referencję)
                    bind.addr = actualAddr;
                    frame[param.uid] = bind;

                } else if (param.mode == 'I') {
                    // IN → przez wartość
                    int local = getTmpAddr("__in_" + std::to_string(param.uid) + "_" + std::to_string(newLabel()));
                    emit("LOAD " + std::to_string(actualAddr));
                    emit("STORE " + std::to_string(local));

                    bind.addr = local;
                    frame[param.uid] = bind;
                } else if (param.mode == 'O') {
                    int local = getTmpAddr("__out_" + std::to_string(param.uid) + "_" + std::to_string(newLabel()));
                    bind.addr = local;
                    frame[param.uid] = bind;
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

    int itAddr = symtab.lookupByUid(f->iteratorUid)->addr;

    // iterator widoczny w ciele pętli
    std::unordered_map<int, ParamBinding> itFrame;
    itFrame[f->iteratorUid] = ParamBinding{ itAddr, false };
    paramEnv.push_back(std::move(itFrame));

    // Zamrażamy granicę "to" (żeby nie przeliczać i nie zależeć od iteratora)
    int limitAddr = getTmpAddr("__for_limit_" + std::to_string(newLabel()));
    genExpr(f->to.get());
    emit("STORE " + std::to_string(limitAddr));

    // i := from
    genExpr(f->from.get());
    emit("STORE " + std::to_string(itAddr));

    int loopLabel = newLabel();
    int bodyLabel = newLabel();
    int endLabel  = newLabel();

    markLabel(loopLabel);

    // Oblicz diff = i - limit
    emit("LOAD " + std::to_string(itAddr));      // a = i
    emit("SWP b");                               // b = i
    emit("LOAD " + std::to_string(limitAddr));   // a = limit
    emit("SWP b");                               // b = limit, a = i
    emit("SUB b");                               // a = i - limit

    if (!f->downto) {
        // TO: kontynuuj gdy i <= limit  <=> (i - limit) <= 0
        // wyjście gdy i > limit <=> (i - limit) > 0
        emit("JPOS @L" + std::to_string(endLabel));
        emit("JUMP @L" + std::to_string(bodyLabel));
    } else {
        // DOWNTO: kontynuuj gdy i >= limit <=> (i - limit) >= 0
        // wyjście gdy i < limit  <=> (i - limit) < 0
        // brak JNEG -> jeśli nie JPOS i nie JZERO, to musi być <0
        emit("JPOS @L" + std::to_string(bodyLabel));
        emit("JZERO @L" + std::to_string(bodyLabel));
        emit("JUMP @L" + std::to_string(endLabel));
    }

    markLabel(bodyLabel);
    genStmt(f->body.get());

    // i++ / i--
    emit("LOAD " + std::to_string(itAddr));
    if (f->downto) emit("DEC a");
    else          emit("INC a");
    emit("STORE " + std::to_string(itAddr));

    emit("JUMP @L" + std::to_string(loopLabel));
    markLabel(endLabel);

    paramEnv.pop_back();
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
                    // Wejście: po genExpr(left); SWP b; genExpr(right):
                    //   b = left  (multiplicand)
                    //   a = right (multiplier)

                    int Lloop = newLabel();
                    int Lskip = newLabel();
                    int Lend  = newLabel();

                    int addrA    = getTmpAddr("__mul_a_" + std::to_string(Lloop));
                    int addrB    = getTmpAddr("__mul_b_" + std::to_string(Lloop));
                    int addrRes  = getTmpAddr("__mul_r_" + std::to_string(Lloop));
                    int addrEven = getTmpAddr("__mul_e_" + std::to_string(Lloop));

                    // A = multiplicand (left)  [jest w b]
                    emit("SWP b");                  // a = left
                    emit("STORE " + std::to_string(addrA));

                    // B = multiplier (right)   [jest w b po swapie]
                    emit("SWP b");                  // a = right
                    emit("STORE " + std::to_string(addrB));

                    // res = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(addrRes));

                    markLabel(Lloop);

                    // if B == 0 -> end
                    emit("LOAD " + std::to_string(addrB));
                    emit("JZERO @L" + std::to_string(Lend));

                    // even = 2*(B/2)
                    emit("LOAD " + std::to_string(addrB));
                    emit("SHR a");
                    emit("SHL a");
                    emit("STORE " + std::to_string(addrEven));

                    // if B - even == 0 -> skip add
                    emit("LOAD " + std::to_string(addrEven));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(addrB));
                    emit("SUB b");
                    emit("JZERO @L" + std::to_string(Lskip));

                    // res += A
                    emit("LOAD " + std::to_string(addrA));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(addrRes));
                    emit("ADD b");
                    emit("STORE " + std::to_string(addrRes));

                    markLabel(Lskip);

                    // A <<= 1
                    emit("LOAD " + std::to_string(addrA));
                    emit("SHL a");
                    emit("STORE " + std::to_string(addrA));

                    // B >>= 1
                    emit("LOAD " + std::to_string(addrB));
                    emit("SHR a");
                    emit("STORE " + std::to_string(addrB));

                    emit("JUMP @L" + std::to_string(Lloop));

                    markLabel(Lend);
                    emit("LOAD " + std::to_string(addrRes));
                    break;
                }
                case BinOp::DIV:
                case BinOp::MOD: {
                    bool isMod = (b->op == BinOp::MOD);

                    int L1    = newLabel();
                    int L2    = newLabel();
                    int Lskip = newLabel();
                    int Lend  = newLabel();
                    int Ldiv0 = newLabel();

                    // UWAGA: adresy tempów wyliczamy RAZ
                    int addrA = getTmpAddr("__div_a_" + std::to_string(L1)); // dividend
                    int addrB = getTmpAddr("__div_b_" + std::to_string(L1)); // divisor
                    int addrQ = getTmpAddr("__div_q_" + std::to_string(L1)); // quotient
                    int addrC = getTmpAddr("__div_c_" + std::to_string(L1)); // counter

                    // Wejście po genExpr(left); SWP b; genExpr(right):
                    //   b = left (dividend)
                    //   a = right (divisor)

                    // B = divisor (right)  [jest w a]
                    emit("STORE " + std::to_string(addrB));

                    // A = dividend (left)  [jest w b]
                    emit("SWP b");                      // a = left, b = right
                    emit("STORE " + std::to_string(addrA));
                    emit("SWP b");                      // przywróć: a = right, b = left (opcjonalne, ale bezpieczne)

                    // if B == 0 -> 0
                    emit("LOAD " + std::to_string(addrB));
                    emit("JZERO @L" + std::to_string(Ldiv0));

                    // Q = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(addrQ));

                    // C = 1
                    emit("RST a");
                    emit("INC a");
                    emit("STORE " + std::to_string(addrC));

                    // ===== L1 ...
                    markLabel(L1);

                    emit("LOAD " + std::to_string(addrB));
                    emit("SHL a");
                    emit("SWP b");
                    emit("LOAD " + std::to_string(addrA));
                    emit("SWP b");
                    emit("SUB b");
                    emit("JPOS @L" + std::to_string(L2));

                    emit("LOAD " + std::to_string(addrB));
                    emit("SHL a");
                    emit("STORE " + std::to_string(addrB));

                    emit("LOAD " + std::to_string(addrC));
                    emit("INC a");
                    emit("STORE " + std::to_string(addrC));

                    emit("JUMP @L" + std::to_string(L1));

                    // ===== L2 ...
                    markLabel(L2);

                    emit("LOAD " + std::to_string(addrC));
                    emit("JZERO @L" + std::to_string(Lend));

                    emit("LOAD " + std::to_string(addrQ));
                    emit("SHL a");
                    emit("STORE " + std::to_string(addrQ));

                    emit("LOAD " + std::to_string(addrA));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(addrB));
                    emit("SUB b");
                    emit("JPOS @L" + std::to_string(Lskip));

                    emit("LOAD " + std::to_string(addrB));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(addrA));
                    emit("SUB b");
                    emit("STORE " + std::to_string(addrA));

                    emit("LOAD " + std::to_string(addrQ));
                    emit("INC a");
                    emit("STORE " + std::to_string(addrQ));

                    markLabel(Lskip);

                    emit("LOAD " + std::to_string(addrB));
                    emit("SHR a");
                    emit("STORE " + std::to_string(addrB));

                    emit("LOAD " + std::to_string(addrC));
                    emit("DEC a");
                    emit("STORE " + std::to_string(addrC));

                    emit("JUMP @L" + std::to_string(L2));

                    markLabel(Ldiv0);
                    emit("RST a");
                    emit("JUMP @L" + std::to_string(Lend));

                    markLabel(Lend);
                    if (isMod) emit("LOAD " + std::to_string(addrA));
                    else       emit("LOAD " + std::to_string(addrQ));
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
