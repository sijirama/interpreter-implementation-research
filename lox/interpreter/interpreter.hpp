#pragma once

#include <memory>
#include "../AST/Expr.h"

class Interpreter : Expr::Visitor {
  private:
    std::string result;
    CustomAny evaluate(shared_ptr<Expr> expr);
    bool isTruthy(CustomAny value);
    bool isEqual(CustomAny a, CustomAny b);

  public:
    CustomAny visitLiteralExpr(Literal& expr);
    CustomAny visitGroupingExpr(Grouping& expr);
    CustomAny visitUnaryExpr(Unary& expr);
    CustomAny visitBinaryExpr(Binary& expr);
};
