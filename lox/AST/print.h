#ifndef ASTPRINT_H
#define ASTPRINT_H

#include <any>
#include <sstream>
#include <string>
#include "../utils/util.h"
#include "Expr.h"

class ASTPrinter : Expr::Visitor {
  private:
    std::string result;

    CustomAny parenthesize(const std::string& name,
                           std::initializer_list<const Expr*> exprs) {
        std::ostringstream builder;
        builder << "(" << name;

        for (const Expr* expr : exprs) {
            builder << " ";
            std::string previous_result = result;
            expr->accept(*this);
            builder << result;
            result = previous_result;
        }

        builder << ")";
        return CustomAny(builder.str());
    }

  public:
    std::string print(Expr& expr) {
        CustomAny result = expr.accept(*this);
        return result.toString();
    }

    CustomAny visitBinaryExpr(const Binary& expr) override {
        return parenthesize(expr.operatorToken.literal.toString(),
                            {expr.left.get(), expr.right.get()});
    }

    CustomAny visitGroupingExpr(const Grouping& expr) override {
        return parenthesize("group", {expr.expression.get()});
    }

    CustomAny visitLiteralExpr(const Literal& expr) override {
        return expr.value;
    }

    CustomAny visitUnaryExpr(const Unary& expr) override {
        return parenthesize(expr.operatorToken.literal.toString(),
                            {expr.right.get()});
    }
};

#endif
