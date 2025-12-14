#include "codegen.hpp"

std::unordered_map<std::string, int> memory;
int nextAddr = 0;

int getAddr(const std::string& name) {
    if (!memory.count(name))
        memory[name] = nextAddr++;
    return memory[name];
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
            emit("STORE " + std::to_string(getAddr(a->lhs)));
            break;
        }
        case StmtKind::READ: {
            auto r = static_cast<const ReadStmt*>(s);
            emit("READ " + std::to_string(getAddr(r->name)));
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
            int bodyLabel  = newLabel();
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
            emit("STORE " + std::to_string(getAddr(f->iterator)));

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
            emit("STORE " + std::to_string(getAddr(counter)));

            markLabel(startLabel);
            emit("LOAD " + std::to_string(getAddr(counter)));
            emit("JZERO @L" + std::to_string(endLabel));

            // body
            genStmt(f->body.get());

            // iterator ++ / --
            emit("LOAD " + std::to_string(getAddr(f->iterator)));
            if (f->downto)
                emit("DEC a");
            else
                emit("INC a");
            emit("STORE " + std::to_string(getAddr(f->iterator)));

            // cnt--
            emit("LOAD " + std::to_string(getAddr(counter)));
            emit("DEC a");
            emit("STORE " + std::to_string(getAddr(counter)));

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
            emit("LOAD " + std::to_string(getAddr(v->name)));
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
                    emit("STORE " + std::to_string(getAddr(mulTmp)));

                    // res = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(getAddr(mulRes)));

                    // multiplicand jest w rb (left) – zostawiamy w rb

                    markLabel(loopLabel);

                    // if tmp == 0 -> end
                    emit("LOAD " + std::to_string(getAddr(mulTmp)));
                    emit("JZERO @L" + std::to_string(endLabel));

                    // sprawdź nieparzystość: tmp - 2*(tmp/2)
                    emit("SHR a");
                    emit("SHL a");
                    emit("SWP b"); // b = evenPart, a = multiplicand (było w b)  -> UWAGA: utrzymujemy b jako evenPart
                    emit("LOAD " + std::to_string(getAddr(mulTmp)));
                    emit("SUB b");
                    emit("JZERO @L" + std::to_string(skipLabel));

                    // res += multiplicand (multiplicand trzeba mieć w b)
                    emit("SWP b"); // b = multiplicand, a = (tmp - evenPart)
                    emit("LOAD " + std::to_string(getAddr(mulRes)));
                    emit("ADD b");
                    emit("STORE " + std::to_string(getAddr(mulRes)));

                    markLabel(skipLabel);

                    // multiplicand <<= 1  (b *= 2)
                    emit("LOAD b");
                    emit("SHL a");
                    emit("SWP b");

                    // tmp >>= 1
                    emit("LOAD " + std::to_string(getAddr(mulTmp)));
                    emit("SHR a");
                    emit("STORE " + std::to_string(getAddr(mulTmp)));

                    emit("JUMP @L" + std::to_string(loopLabel));

                    markLabel(endLabel);
                    emit("LOAD " + std::to_string(getAddr(mulRes)));
                    break;
                }
                case BinOp::DIV:
                case BinOp::MOD: {
                    bool isMod = (b->op == BinOp::MOD);

                    int loop1 = newLabel();
                    int loop2 = newLabel();
                    int skip = newLabel();
                    int end   = newLabel();

                    std::string A = "__div_a_" + std::to_string(loop1);
                    std::string B = "__div_b_" + std::to_string(loop1);
                    std::string Q = "__div_q_" + std::to_string(loop1);
                    std::string S = "__div_sh_" + std::to_string(loop1);

                    // start: ra = divisor, rb = dividend
                    // save A = dividend
                    emit("SWP b");           // ra = dividend
                    emit("STORE " + std::to_string(getAddr(A)));

                    // save B = divisor
                    emit("SWP b");           // ra = divisor
                    emit("STORE " + std::to_string(getAddr(B)));

                    // Q = 0, shift = 0
                    emit("RST a");
                    emit("STORE " + std::to_string(getAddr(Q)));
                    emit("STORE " + std::to_string(getAddr(S)));

                    // === first loop: find max shift ===
                    markLabel(loop1);
                    emit("LOAD " + std::to_string(getAddr(B)));
                    emit("SHL a");
                    emit("SWP b");
                    emit("LOAD " + std::to_string(getAddr(A)));
                    emit("SWP b");
                    emit("SUB b");           // (B<<1) - A
                    emit("JPOS @L" + std::to_string(loop2));
                    emit("JPOS @L" + std::to_string(loop2));

                    // B <<= 1, shift++
                    emit("LOAD " + std::to_string(getAddr(B)));
                    emit("SHL a");
                    emit("STORE " + std::to_string(getAddr(B)));

                    emit("LOAD " + std::to_string(getAddr(S)));
                    emit("INC a");
                    emit("STORE " + std::to_string(getAddr(S)));

                    emit("JUMP @L" + std::to_string(loop1));

                    // === second loop: subtract & build quotient ===
                    markLabel(skip);
                    emit("LOAD " + std::to_string(getAddr(S)));
                    emit("JZERO @L" + std::to_string(end));

                    emit("LOAD " + std::to_string(getAddr(A)));
                    emit("SWP b");
                    emit("LOAD " + std::to_string(getAddr(B)));
                    emit("SUB b");
                    emit("JPOS @L" + std::to_string(skip));

                    // A -= B
                    emit("STORE " + std::to_string(getAddr(A)));

                    // Q += (1 << shift)
                    emit("LOAD " + std::to_string(getAddr(Q)));
                    emit("INC a");
                    emit("STORE " + std::to_string(getAddr(Q)));

                    markLabel(loop2);

                    // B >>= 1, shift--
                    emit("LOAD " + std::to_string(getAddr(B)));
                    emit("SHR a");
                    emit("STORE " + std::to_string(getAddr(B)));

                    emit("LOAD " + std::to_string(getAddr(S)));
                    emit("DEC a");
                    emit("STORE " + std::to_string(getAddr(S)));

                    emit("JUMP @L" + std::to_string(loop2));

                    markLabel(end);
                    if (isMod)
                        emit("LOAD " + std::to_string(getAddr(A)));
                    else
                        emit("LOAD " + std::to_string(getAddr(Q)));
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
