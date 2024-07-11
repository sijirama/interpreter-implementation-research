#include <sstream>
#include "../AST/Expr.h"

class RPNPrinter : public Expr::Visitor {
  private:
    std::string result;

  public:
    std::string print(Expr& expr) {
        expr.accept(*this);
        return result;
    }

    void parenthesize(const std::string& name,
                      std::initializer_list<const Expr*> exprs) {
        std::ostringstream builder;
        builder << "(";

        for (const Expr* expr : exprs) {
            builder << " ";
            std::string previous_result = result;
            expr->accept(*this);
            builder << result;
            result = previous_result;
        }

        builder << name << ")";
        result = builder.str();
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
