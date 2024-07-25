#pragma once

#include <memory>
#include "../AST/Expr.h"

class Interpreter : Expr::Visitor {
  private:
    std::string result;
    CustomAny evaluate(shared_ptr<Expr> expr);
    bool isTruthy(CustomAny value);
    bool isEqual(CustomAny a, CustomAny b);
    void checkNumberOperand(Token op, CustomAny operand);

    template <typename... Args>
    void checkNumberOperands(const Token& op, const Args&... args);

  public:
    std::string stringify(const CustomAny& object);
    CustomAny interprete(shared_ptr<Expr> expression);
    CustomAny visitLiteralExpr(const Literal& expr) override;
    CustomAny visitGroupingExpr(const Grouping& expr) override;
    CustomAny visitUnaryExpr(const Unary& expr) override;
    CustomAny visitBinaryExpr(const Binary& expr) override;
};
