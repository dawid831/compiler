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

enum class StmtKind {
    ASSIGN,
    READ,
    WRITE,
    BLOCK
};

struct Stmt {
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

