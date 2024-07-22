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
    CustomAny visitLiteralExpr(Literal& expr);
    CustomAny visitGroupingExpr(Grouping& expr);
    CustomAny visitUnaryExpr(Unary& expr);
    CustomAny visitBinaryExpr(Binary& expr);
};
