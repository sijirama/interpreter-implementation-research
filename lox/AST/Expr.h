#ifndef Expr_H
#define Expr_H

#include <any>
#include <memory>
#include <ostream>
#include <string>
#include "../token/token.h"

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
    Binary(std::shared_ptr<Expr> left, Token operatorToken,
           std::shared_ptr<Expr> right)
        : left(std::move(left)), operatorToken(std::move(operatorToken)),
          right(std::move(right)) {}

    void accept(Visitor& visitor) const override {
        visitor.visitBinaryExpr(*this);
    }

    std::shared_ptr<Expr> left;
    Token operatorToken;
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
    Literal(std::any value) {
        cout << "The stuff of the stuff is: " << any_cast<string>(&value)
             << endl;
        this->value = value;
    }

    void accept(Visitor& visitor) const override {
        visitor.visitLiteralExpr(*this);
    }

    void printValue() {
        std::cout << "WHAT IS THE NAME OF THE VALUE" << std::endl;
        std::cout << "WHAT IS THE NAME OF THE VALUE" << std::endl;
        std::cout << any_cast<string>(&value) << std::endl;
        std::cout << "The value is:" << any_cast<string>(&value) << " <--- "
                  << std::endl;
    }

    std::any value;
};

class Unary : public Expr {
  public:
    Unary(Token operatorToken, std::shared_ptr<Expr> right)
        : operatorToken(std::move(operatorToken)), right(std::move(right)) {}

    void accept(Visitor& visitor) const override {
        visitor.visitUnaryExpr(*this);
    }

    Token operatorToken;
    std::shared_ptr<Expr> right;
};

#endif
