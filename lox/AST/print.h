#ifndef ASTPRINT_H
#define ASTPRINT_H

#include <sstream>
#include <string>
#include "Expr.h"

class ASTPrinter : Expr::Visitor {
  private:
    std::string result;

    void parenthesize(const std::string& name,
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
        result = builder.str();
    }

  public:
    std::string print(Expr& expr) {
        expr.accept(*this);
        return result;
    }

    void visitBinaryExpr(const Binary& expr) override {
        parenthesize(expr.operatorToken, {expr.left.get(), expr.right.get()});
    }

    void visitGroupingExpr(const Grouping& expr) override {
        parenthesize("group", {expr.expression.get()});
    }

    void visitLiteralExpr(const Literal& expr) override {
        result = expr.value.empty() ? "nil" : expr.value;
    }

    void visitUnaryExpr(const Unary& expr) override {
        parenthesize(expr.operatorToken, {expr.right.get()});
    }
};

#endif
