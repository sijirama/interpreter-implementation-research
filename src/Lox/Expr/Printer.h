
#pragma once

#include <any>
#include <sstream>
#include <string>

#include "BinaryExpr.h"
#include "Expr.h"
#include "ExprVisitor.h"
#include "GroupingExpr.h"
#include "LiteralExpr.h"
#include "UnaryExpr.h"

namespace Lox {
    class AstPrinter : public ExprVisitor<std::any> {
        private:
            std::string result;

            std::string parenthesize(const std::string& name,
                                     std::initializer_list<const Expr*> exprs) {
                std::ostringstream builder;  // StringBuilder equivalent in C++
                builder << "(" << name;

                for (const Expr* expr : exprs) {
                    builder << " ";
                    std::string previous_result = result;
                    expr->accept(*this);
                    builder << result;
                    result = previous_result;
                }

                builder << ")";
                return builder.str();
            }

        public:
            std::string print(Expr& expr) {
                return std::any_cast<std::string>(expr.accept(*this));
            }

            std::any visitBinaryExpr(const BinaryExpr& expr) override {
                return parenthesize(expr.getOp().literalToString(),
                                    {&expr.getLeftExpr(), &expr.getRightExpr()});
            }

            std::any visitUnaryExpr(const UnaryExpr& expr) override {
                return parenthesize(expr.getOp().literalToString(), {&expr.getRightExpr()});
            }

            std::any visitLiteralExpr(const LiteralExpr& expr) override {
                if (expr.getLiteral().type() == typeid(std::string)) {
                    return std::any_cast<std::string>(expr.getLiteral());
                } else if (expr.getLiteral().type() == typeid(int)) {
                    return std::to_string(std::any_cast<int>(expr.getLiteral()));
                } else if (expr.getLiteral().type() == typeid(double)) {
                    return std::to_string(std::any_cast<double>(expr.getLiteral()));
                }
                return std::string();
            }

            std::any visitGroupingExpr(const GroupingExpr& expr) override {
                return parenthesize("group", {&expr.getExpr()});
            }
    };
}  // namespace Lox
