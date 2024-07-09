#ifndef Expr_H
#define Expr_H

#include <memory>
#include <string>

class Expr {
  public:
    virtual ~Expr() = default;

    class Visitor {
      public:
        virtual ~Visitor() = default;
        virtual void visitBinaryExpr(const class Binary& expr) = 0;
        virtual void visitGroupingExpr(const class Grouping& expr) = 0;
        virtual void visitLiteralExpr(const class Literal& expr) = 0;
        virtual void visitUnaryExpr(const class Unary& expr) = 0;
    };

    virtual void accept(Visitor& visitor) const = 0;
};

class Binary : public Expr {
  public:
    Binary(std::shared_ptr<Expr> left, std::string operatorToken,
           std::shared_ptr<Expr> right)
        : left(std::move(left)), operatorToken(std::move(operatorToken)),
          right(std::move(right)) {}

    void accept(Visitor& visitor) const override {
        visitor.visitBinaryExpr(*this);
    }

    std::shared_ptr<Expr> left;
    std::string operatorToken;
    std::shared_ptr<Expr> right;
};

class Grouping : public Expr {
  public:
    explicit Grouping(std::shared_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    void accept(Visitor& visitor) const override {
        visitor.visitGroupingExpr(*this);
    }

    std::shared_ptr<Expr> expression;
};

class Literal : public Expr {
  public:
    explicit Literal(std::string value) : value(std::move(value)) {}

    void accept(Visitor& visitor) const override {
        visitor.visitLiteralExpr(*this);
    }

    std::string value;
};

class Unary : public Expr {
  public:
    Unary(std::string operatorToken, std::shared_ptr<Expr> right)
        : operatorToken(std::move(operatorToken)), right(std::move(right)) {}

    void accept(Visitor& visitor) const override {
        visitor.visitUnaryExpr(*this);
    }

    std::string operatorToken;
    std::shared_ptr<Expr> right;
};

#endif
