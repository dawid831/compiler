#include "codegen.hpp"
#include "symbol_table.hpp"

// Globalna tabela symboli (zmienne globalne, lokalne, parametry procedur)
extern SymbolTable symtab;

struct ParamBinding {
    int addr = -1;
    // addr:
    //  - dla skalarów: bezpośredni adres komórki pamięci
    //  - dla tablic: adres bazowy tablicy (pierwszego elementu)

    bool isArray = false;
    // czy parametr formalny jest tablicą (mode == 'T')

    long long arrStart = 0;
    long long arrEnd = 0;
    // faktyczny zakres tablicy przekazanej w wywołaniu
};

// paramEnv działa jak STACK wywołań procedur:
//
// paramEnv.back()   -> aktualnie wykonywana procedura
// paramEnv.front()  -> pierwsza (najbardziej zewnętrzna)
//
// Klucz: uid parametru formalnego
// Wartość: ParamBinding (adres, czy tablica, zakres)
std::vector<std::unordered_map<int, ParamBinding>> paramEnv;

int nextAddr = 0;

void CodeGen::allocateAllSymbols() {
    // Przechodzimy po WSZYSTKICH symbolach (ze wszystkich scope'ów)
    // UID → Symbol
    // Alokacja jest globalna i JEDNORAZOWA

    for (auto& [uid, s] : symtab.getUidMap()) {
        if (s.addr != -1) continue;

        s.addr = nextAddr;

        if (s.kind == SymbolKind::ARRAY) {
            // tablica zajmuje (end-start+1) komórek
            nextAddr += (s.end - s.start + 1);
        } else {
            // skalar zajmuje 1 komórkę
            nextAddr += 1;
        }
    }
}

int getTmpAddr(const std::string&) {
    // Każde wywołanie daje NOWY adres
    // Nigdy nie jest zwalniany (ale to OK – program jest krótki)
    return nextAddr++;
}

int resolveAddr(const VarExpr* v) {
    // 1. Najpierw sprawdzamy, czy to parametr procedury (albo iterator FOR)
    //    – wtedy jego adres pochodzi z paramEnv
    for (auto it = paramEnv.rbegin(); it != paramEnv.rend(); ++it)
        if (it->count(v->uid))
            return (*it)[v->uid].addr;

    // 2. W przeciwnym razie – zwykła zmienna globalna/lokalna
    const Symbol* s = symtab.lookupByUid(v->uid);
    if (!s || s->addr < 0) {
        std::cerr << "INTERNAL ERROR: unresolved variable addr\n";
        exit(1);
    }
    return s->addr;
}

// Funkcja flush() wykonuje FINALIZACJĘ kodu maszynowego.
//
// W trakcie generowania kodu skoki (JUMP, JZERO, JPOS)
// nie znają jeszcze docelowych adresów instrukcji.
// Zamiast tego używane są symboliczne etykiety postaci @L<number>.
//
// flush():
//  1) przechodzi po wszystkich wygenerowanych liniach kodu,
//  2) wyszukuje symboliczne etykiety @Lx,
//  3) zastępuje je rzeczywistymi numerami instrukcji,
//     zapisanymi wcześniej w mapie labelPos,
//  4) wypisuje finalny kod maszynowy na stdout.
//
// Jeśli jakaś etykieta nie została zdefiniowana (brak w labelPos),
// kompilator kończy się błędem wewnętrznym.
void CodeGen::flush() {

    // Przechodzimy po wszystkich wygenerowanych liniach kodu maszynowego.
    // Każda linia to jedna instrukcja lub dyrektywa (string).
    for (auto& line : lines) {

        // p = aktualna pozycja wyszukiwania w danej linii
        size_t p = 0;

        // Szukamy wszystkich wystąpień "@L" w linii,
        // ponieważ w jednej instrukcji może wystąpić więcej niż jedna etykieta
        // (teoretycznie, choć w praktyce raczej jedna).
        while ((p = line.find("@L", p)) != std::string::npos) {

            // numStart – początek numeru etykiety (zaraz po "@L")
            size_t numStart = p + 2;
            size_t numEnd = numStart;

            // Przesuwamy numEnd tak długo, jak długo są to cyfry,
            // aby wyciągnąć pełny numer etykiety (np. @L123)
            while (numEnd < line.size() &&
                   isdigit((unsigned char)line[numEnd])) {
                numEnd++;
            }

            // Jeśli po "@L" nie było żadnej cyfry,
            // mamy błędnie wygenerowaną etykietę (np. "@L ")
            if (numEnd == numStart) {
                std::cerr << "INTERNAL ERROR: malformed label in: "
                          << line << "\n";
                exit(1);
            }

            // Parsujemy numer etykiety, np. z "@L42" → 42
            int lab = std::stoi(line.substr(numStart, numEnd - numStart));

            // Szukamy rzeczywistej pozycji tej etykiety w kodzie
            // labelPos mapuje: label → numer instrukcji
            auto it = labelPos.find(lab);
            if (it == labelPos.end()) {
                // Jeśli etykieta nie została nigdy oznaczona przez markLabel(),
                // to znaczy, że kod generatora jest logicznie błędny
                std::cerr << "INTERNAL ERROR: unresolved label "
                          << lab << "\n";
                exit(1);
            }

            // Zamieniamy "@L<nr>" na konkretny numer instrukcji
            // np. "JUMP @L5" → "JUMP 37"
            line.replace(p, numEnd - p, std::to_string(it->second));

            // Przesuwamy p za wstawiony numer,
            // aby uniknąć zapętlenia wyszukiwania
            p += std::to_string(it->second).size();
        }
    }

    // Po podmienieniu wszystkich etykiet
    // wypisujemy gotowy kod maszynowy na stdout
    for (auto& line : lines) {
        std::cout << line << "\n";
    }
}


// Generowanie kodu dla stałej wartosci liczbowej
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

// Generowanie kodu dla wyrażenia warunkowego
// SPRAWDZONE, NIE ZMIENIAC BEZ POWODU
void CodeGen::emitCondJump(const CondExpr* cond,
                           int labelTrue,
                           int labelFalse)
{
    switch (cond->op) {

    case CondOp::EQ:
        // left - right == 0 and right - left == 0
        // a = left
        genExpr(cond->left.get());
        emit("SWP b");              // b = left

        // a = right
        genExpr(cond->right.get());
        emit("SUB b");              // a = max(right - left, 0)
        emit("JPOS @L" + std::to_string(labelFalse)); // jeśli >0 -> nie równe

        // teraz sprawdzamy drugą stronę
        genExpr(cond->right.get());
        emit("SWP b");              // b = right
        genExpr(cond->left.get());
        emit("SUB b");              // a = max(left - right, 0)
        emit("JPOS @L" + std::to_string(labelFalse)); // jeśli >0 -> nie równe

        // jeśli oba = 0 → równe
        emit("JUMP @L" + std::to_string(labelTrue));
        break;

    case CondOp::NEQ:
        // left - right > 0 lub  right - left > 0
        // right - left
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelTrue));

        // left - right
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SUB b");
        emit("JPOS @L" + std::to_string(labelTrue));

        // inaczej równe
        emit("JUMP @L" + std::to_string(labelFalse));
        break;

    case CondOp::LT:
        // left < right  ===  (right - left) > 0
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SUB b");                         // a = right - left 
        emit("JPOS  @L" + std::to_string(labelTrue));
        emit("JUMP  @L" + std::to_string(labelFalse));
    break;

    case CondOp::GT:
        // left > right === (left - right) > 0
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SUB b");                         // a = left - right 
        emit("JPOS  @L" + std::to_string(labelTrue));
        emit("JUMP  @L" + std::to_string(labelFalse));
        break;

    case CondOp::LEQ:
        // left <= right  <=>  !(left > right) === !(left - right > 0)
        // sprawdzamy (left - right) > 0 => FAŁSZ, wpp. PRAWDA
        genExpr(cond->right.get());
        emit("SWP b");
        genExpr(cond->left.get());
        emit("SUB b");               // left - right
        emit("JPOS  @L" + std::to_string(labelFalse));
        emit("JUMP  @L" + std::to_string(labelTrue));
        break;

    case CondOp::GEQ:
        // left >= right  <=>  !(left < right)  <=>  !(right - left > 0)
        genExpr(cond->left.get());
        emit("SWP b");
        genExpr(cond->right.get());
        emit("SUB b");               // right - left
        emit("JPOS  @L" + std::to_string(labelFalse));
        emit("JUMP  @L" + std::to_string(labelTrue));
        break;
    }
}


int getForCounterAddr() {
    static int forBase = 100000; // albo > max symboli
    return forBase++;
}

void CodeGen::emitArrayAddrToC(const VarExpr* arr) {
    // tmp na offset
    int tmpOffset = getTmpAddr("__idx_" + std::to_string(newLabel()));

    // 1) offset = index
    genExpr(arr->index.get());     // a = index

    // ustal start i bazę
    long long start = arr->arrStart;
    int baseAddr = resolveAddr(arr);

    for (size_t i = paramEnv.size(); i-- > 0; ) {
        auto it = paramEnv[i].find(arr->uid);
        if (it != paramEnv[i].end() && it->second.isArray) {
            start    = it->second.arrStart;
            baseAddr = it->second.addr;
            break;
        }
    }

    // 2) offset -= start
    if (start != 0) {
        genConst(start);        // a = start
        emit("SWP c");          // c = start
        genExpr(arr->index.get()); // a = index
        emit("SUB c");          // a = index - start
    }

    emit("STORE " + std::to_string(tmpOffset)); // zapisz offset

    // 3) a = base
    genConst(baseAddr);

    // 4) a = base + offset (przez b, ale z backupem)
    emit("SWP c");                              // c = base
    emit("LOAD " + std::to_string(tmpOffset)); // a = offset
    emit("ADD c");                              // a = base + offset

    // 5) c = adres
    emit("SWP c");
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
                // lhs jest tablicą: A[idx] := rhs

                int lhsAddrTmp = getTmpAddr("__lhs_addr_" + std::to_string(newLabel()));
                int rhsTmp     = getTmpAddr("__rhs_"     + std::to_string(newLabel()));

                // 1) policz adres elementu i zapisz go
                emitArrayAddrToC(a->lhs.get());   // c = addr(A[idx])
                emit("RST a");
                emit("ADD c");                    // a = c
                emit("STORE " + std::to_string(lhsAddrTmp));

                // 2) policz RHS i zapisz go
                genExpr(a->rhs.get());            // a = rhs
                emit("STORE " + std::to_string(rhsTmp));

                // 3) odtwórz adres i wykonaj zapis
                emit("LOAD " + std::to_string(lhsAddrTmp));
                emit("SWP c");                    // c = addr(A[idx])
                emit("LOAD " + std::to_string(rhsTmp));
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
                int lhsAddrTmp = getTmpAddr("__read_lhs_" + std::to_string(newLabel()));
                int valTmp     = getTmpAddr("__read_val_" + std::to_string(newLabel()));

                emit("READ");
                emit("STORE " + std::to_string(valTmp));

                emitArrayAddrToC(r->target.get());   // c = addr(A[idx])
                emit("RST a");
                emit("ADD c");
                emit("STORE " + std::to_string(lhsAddrTmp));

                emit("LOAD " + std::to_string(lhsAddrTmp));
                emit("SWP c");
                emit("LOAD " + std::to_string(valTmp));
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
                // kluczowe: adres argumentu wyliczamy przez resolveAddr, żeby działało także gdy argument jest parametrem innej procedury
                VarExpr actualDummy("__arg", actualUid);
                int actualAddr = resolveAddr(&actualDummy);

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
            int endLabel   = newLabel();

            markLabel(startLabel);

            // jeśli warunek FAŁSZ → end
            emitCondJump(w->cond.get(),
                        /*true*/  newLabel(),  // tymczasowy
                        /*false*/ endLabel);

            int bodyLabel = labelCounter - 1; // to jest label true

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
            auto *f = static_cast<const ForStmt*>(s);

            VarExpr iterExpr(f->iterator, f->iteratorUid);

            int itAddr = resolveAddr(&iterExpr);
            static int tmpCounter = 0;

            int fromAddr = getTmpAddr("__from");
            int toAddr   = getTmpAddr("__to");
            int cntAddr  = getTmpAddr("__cnt");

            int L_start   = newLabel();
            int L_body    = newLabel();
            int L_end     = newLabel();
            int L_noIters = newLabel();

            /* --- zamrażamy FROM i TO --- */

            genExpr(f->from.get());
            emit("STORE " + std::to_string(fromAddr));

            genExpr(f->to.get());
            emit("STORE " + std::to_string(toAddr));

            /* --- iterator := from --- */

            emit("LOAD " + std::to_string(fromAddr));
            emit("STORE " + std::to_string(itAddr));

            /* --- wyliczamy cnt (liczbę iteracji) --- */

            /* --- wyliczamy cnt (liczbę iteracji) --- */
            if (!f->downto) {
                // TO: pusta gdy from > to  ⇔  (from - to) > 0

                emit("LOAD " + std::to_string(toAddr));
                emit("SWP b");                            // b = to
                emit("LOAD " + std::to_string(fromAddr)); // a = from
                emit("SUB b");                            // a = from - to
                emit("JPOS @L" + std::to_string(L_noIters));

                // cnt = (to - from) + 1
                emit("LOAD " + std::to_string(fromAddr));
                emit("SWP b");                            // b = from
                emit("LOAD " + std::to_string(toAddr));   // a = to
                emit("SUB b");                            // a = to - from
                emit("INC a");
                emit("STORE " + std::to_string(cntAddr));
            } else {
                // DOWNTO: pusta gdy from < to ⇔ (to - from) > 0

                emit("LOAD " + std::to_string(fromAddr));
                emit("SWP b");                            // b = from
                emit("LOAD " + std::to_string(toAddr));   // a = to
                emit("SUB b");                            // a = to - from
                emit("JPOS @L" + std::to_string(L_noIters));

                // cnt = (from - to) + 1
                emit("LOAD " + std::to_string(toAddr));
                emit("SWP b");                            // b = to
                emit("LOAD " + std::to_string(fromAddr)); // a = from
                emit("SUB b");                            // a = from - to
                emit("INC a");
                emit("STORE " + std::to_string(cntAddr));
            }
            markLabel(L_start);

            // jeśli cnt == 0 → koniec
            emit("LOAD " + std::to_string(cntAddr));
            emit("JZERO @L" + std::to_string(L_end));

            // cnt--
            emit("DEC a");
            emit("STORE " + std::to_string(cntAddr));

            markLabel(L_body);

            // ciało pętli
            genStmt(f->body.get());

            // iterator++ / iterator--
            emit("LOAD " + std::to_string(itAddr));
            if (!f->downto) emit("INC a");
            else           emit("DEC a");
            emit("STORE " + std::to_string(itAddr));

            emit("JUMP @L" + std::to_string(L_start));

            /* --- brak iteracji --- */

            markLabel(L_noIters);
            markLabel(L_end);
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
