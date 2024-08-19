#ifndef Expr_H
#define Expr_H

#include <any>
#include <memory>
#include <ostream>
#include <string>
#include "../token/token.h"
#include "../utils/customAny.hpp"

using namespace std;

class Expr {
  public:
    virtual ~Expr() = default;

    class Visitor {
      public:
        virtual ~Visitor() = default;
        virtual CustomAny visitBinaryExpr(const class Binary& expr) = 0;
        virtual CustomAny visitGroupingExpr(const class Grouping& expr) = 0;
        virtual CustomAny visitLiteralExpr(const class Literal& expr) = 0;
        virtual CustomAny visitUnaryExpr(const class Unary& expr) = 0;
    };

    virtual CustomAny accept(Visitor& visitor) const = 0;
};

class Binary : public Expr {
  public:
    Binary(std::shared_ptr<Expr> left, Token operatorToken,
           std::shared_ptr<Expr> right)
        : left(std::move(left)), operatorToken(std::move(operatorToken)),
          right(std::move(right)) {}

    CustomAny accept(Visitor& visitor) const override {
        return visitor.visitBinaryExpr(*this);
    }

    std::shared_ptr<Expr> left;
    Token operatorToken;
    std::shared_ptr<Expr> right;
};

class Grouping : public Expr {
  public:
    explicit Grouping(std::shared_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    CustomAny accept(Visitor& visitor) const override {
        return visitor.visitGroupingExpr(*this);
    }

    std::shared_ptr<Expr> expression;
};

class Literal : public Expr {
  public:
    Literal(std::any value) : value(value) {
        // cout << "The stuff of the stuff is: " << th  << endl;
        cout << "The stuff of the stuff is: " << any_cast<string>(&value)
             << endl;
        this->value = value;
        auto type = value.type().name();
        std::cout << "we check for the type in the constructor of the arg and"
                     "it gives us: "
                  << type << std::endl;
    }

    CustomAny accept(Visitor& visitor) const override {
        return visitor.visitLiteralExpr(*this);
    }

    void printValue() {
        std::cout << "WHAT IS THE NAME OF THE VALUE" << std::endl;
        std::cout << value.getType().name() << std::endl;
        std::cout << "The value is:" << value.toString() << " <--- "
                  << std::endl;

        std::cout << "========================================================="
                     "=========================================="
                  << std::endl;
    }

    // std::any value;
    CustomAny value;
};

class Unary : public Expr {
  public:
    Unary(Token operatorToken, std::shared_ptr<Expr> right)
        : operatorToken(std::move(operatorToken)), right(std::move(right)) {}

    CustomAny accept(Visitor& visitor) const override {
        return visitor.visitUnaryExpr(*this);
    }

    Token operatorToken;
    std::shared_ptr<Expr> right;
};

#endif
