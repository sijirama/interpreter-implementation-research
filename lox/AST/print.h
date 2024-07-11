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
        parenthesize(castAny<string>(expr.operatorToken.literal),
                     {expr.left.get(), expr.right.get()});
    }

    void visitGroupingExpr(const Grouping& expr) override {
        parenthesize("group", {expr.expression.get()});
    }

    // void visitLiteralExpr(const Literal& expr) override {
    //     result = expr.value.empty() ? "nil" : expr.value;
    // }

    void visitLiteralExpr(const Literal& expr) override {
        if (expr.value.has_value()) {
            if (expr.value.type() == typeid(std::string)) {
                std::string value = std::any_cast<std::string>(expr.value);
                result = value.empty() ? "nil" : value;
            } else if (expr.value.type() == typeid(bool)) {
                bool value = std::any_cast<bool>(expr.value);
                result = value ? "true" : "false";
            } else if (expr.value.type() == typeid(int)) {
                int value = std::any_cast<int>(expr.value);
                result = std::to_string(value);
            } else {
                // Handle other types as needed
                result = "nil";
            }
        } else {
            result = "nil"; // Handle case where expr.value is empty
        }
    }

    void visitUnaryExpr(const Unary& expr) override {
        parenthesize(castAny<string>(expr.operatorToken), {expr.right.get()});
    }
};

#endif
