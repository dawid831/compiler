#pragma once
#include <string>
#include <memory>
#include <vector>

enum class ExprKind {
    CONST,
    VAR,
    BINOP
};

enum class BinOp {
    ADD, SUB, MUL, DIV, MOD
};

struct Expr {
    ExprKind kind;
    virtual ~Expr() = default;
};

struct ConstExpr : Expr {
    long long value;
    ConstExpr(long long v) : value(v) { kind = ExprKind::CONST; }
};

struct VarExpr : Expr {
    std::string name;
    int uid;
    bool isArray = false;
    long long arrStart = 0;
    long long arrEnd = 0;
    std::unique_ptr<Expr> index;

    VarExpr(const std::string& n, int u, std::unique_ptr<Expr> idx = nullptr)
        : name(n), uid(u), index(std::move(idx)) {
        kind = ExprKind::VAR;
        isArray = (index != nullptr);
    }
};


struct BinExpr : Expr {
    BinOp op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinExpr(BinOp o,
            std::unique_ptr<Expr> l,
            std::unique_ptr<Expr> r)
        : op(o), left(std::move(l)), right(std::move(r)) {
        kind = ExprKind::BINOP;
    }
};

enum class CondOp { EQ, NEQ, LT, GT, LEQ, GEQ };

enum class StmtKind {
    ASSIGN,
    READ,
    WRITE,
    BLOCK,
    CALL,
    IF,
    WHILE,
    REPEAT,
    FOR        
};

struct Stmt {
    StmtKind kind;
    virtual ~Stmt() = default;
};

struct AssignStmt : Stmt {
    std::unique_ptr<VarExpr> lhs;
    std::unique_ptr<Expr> rhs;

    AssignStmt(VarExpr* l, std::unique_ptr<Expr> r)
        : lhs(l), rhs(std::move(r)) {
        kind = StmtKind::ASSIGN;
    }
};

struct ReadStmt : Stmt {
    std::unique_ptr<VarExpr> target;

    ReadStmt(VarExpr* t) : target(t) {
        kind = StmtKind::READ;
    }
};

struct WriteStmt : Stmt {
    std::unique_ptr<Expr> expr;
    WriteStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {
        kind = StmtKind::WRITE;
    }
};

struct BlockStmt : Stmt {
    std::vector<std::unique_ptr<Stmt>> stmts;

    BlockStmt() {
        kind = StmtKind::BLOCK;
    }
};

struct CallArg {
    int uid;
    bool isArray;
    long long start, end;   // ważne dla T (tablica)
};

struct CallStmt : Stmt {
    std::string name;
    std::vector<CallArg> args;
    CallStmt(const std::string& n, std::vector<CallArg> a)
        : name(n), args(std::move(a)) {
        kind = StmtKind::CALL;
    }
};


struct CondExpr {
    CondOp op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    CondExpr(CondOp op,
             std::unique_ptr<Expr> l,
             std::unique_ptr<Expr> r)
        : op(op), left(std::move(l)), right(std::move(r)) {}
};

struct IfStmt : Stmt {
    std::unique_ptr<CondExpr> cond;
    std::unique_ptr<Stmt> thenBranch;
    std::unique_ptr<Stmt> elseBranch;

    IfStmt(std::unique_ptr<CondExpr> c,
           std::unique_ptr<Stmt> t,
           std::unique_ptr<Stmt> e = nullptr)
        : cond(std::move(c)),
          thenBranch(std::move(t)),
          elseBranch(std::move(e)) {
        kind = StmtKind::IF;
    }
};

struct WhileStmt : Stmt {
    std::unique_ptr<CondExpr> cond;
    std::unique_ptr<Stmt> body;

    WhileStmt(std::unique_ptr<CondExpr> c,
              std::unique_ptr<Stmt> b)
        : cond(std::move(c)), body(std::move(b)) {
        kind = StmtKind::WHILE;
    }
};

struct RepeatStmt : Stmt {
    std::unique_ptr<Stmt> body;
    std::unique_ptr<CondExpr> cond;

    RepeatStmt(std::unique_ptr<Stmt> b,
               std::unique_ptr<CondExpr> c)
        : body(std::move(b)), cond(std::move(c)) {
        kind = StmtKind::REPEAT;
    }
};

struct ForStmt : Stmt {
    std::string iterator;
    int iteratorUid;                 // <-- DODAJ
    std::unique_ptr<Expr> from;
    std::unique_ptr<Expr> to;
    std::unique_ptr<Stmt> body;
    bool downto;

    ForStmt(const std::string& it,
            int itUid,               // <-- DODAJ
            std::unique_ptr<Expr> f,
            std::unique_ptr<Expr> t,
            std::unique_ptr<Stmt> b,
            bool d)
        : iterator(it),
          iteratorUid(itUid),
          from(std::move(f)),
          to(std::move(t)),
          body(std::move(b)),
          downto(d)
    {
        kind = StmtKind::FOR;
    }
};
