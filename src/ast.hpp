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
    VarExpr(const std::string& n) : name(n) { kind = ExprKind::VAR; }
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
    NOP          
};

struct Stmt {
    std::unique_ptr<CondExpr> cond;
    StmtKind kind;
    virtual ~Stmt() = default;
};

struct AssignStmt : Stmt {
    std::string lhs;
    std::unique_ptr<Expr> rhs;

    AssignStmt(const std::string& l, std::unique_ptr<Expr> r)
        : lhs(l), rhs(std::move(r)) {
        kind = StmtKind::ASSIGN;
    }
};

struct ReadStmt : Stmt {
    std::string name;
    ReadStmt(const std::string& n) : name(n) {
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

struct CallStmt : Stmt {
    std::string name;

    CallStmt(const std::string& n) : name(n) {
        kind = StmtKind::CALL;
    }
};

struct IfStmt : Stmt {
    std::unique_ptr<Expr> cond;
    std::unique_ptr<Stmt> thenBranch;
    std::unique_ptr<Stmt> elseBranch; // może być nullptr

    IfStmt(std::unique_ptr<Expr> c,
           std::unique_ptr<Stmt> t,
           std::unique_ptr<Stmt> e = nullptr)
        : cond(std::move(c)),
          thenBranch(std::move(t)),
          elseBranch(std::move(e)) {
        kind = StmtKind::IF;
    }
};

struct WhileStmt : Stmt {
    std::unique_ptr<Expr> cond;
    std::unique_ptr<Stmt> body;

    WhileStmt(std::unique_ptr<Expr> c,
              std::unique_ptr<Stmt> b)
        : cond(std::move(c)), body(std::move(b)) {
        kind = StmtKind::WHILE;
    }
};

struct CondExpr {
    CondOp op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};

struct RepeatStmt : Stmt {
    std::unique_ptr<Stmt> body;
    std::unique_ptr<Expr> cond;

    RepeatStmt(std::unique_ptr<Stmt> b,
               std::unique_ptr<Expr> c)
        : body(std::move(b)), cond(std::move(c)) {
        kind = StmtKind::REPEAT;
    }
};


struct NopStmt : Stmt {
    NopStmt() { kind = StmtKind::NOP; }
};
