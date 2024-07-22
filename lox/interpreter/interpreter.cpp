#include "interpreter.hpp"
#include <cstddef>
#include <memory>

bool Interpreter::isEqual(CustomAny a, CustomAny b) {
    if (a.isNull() && b.isNull()) {
        return true;
    }
    if (a.isNull() || b.isNull()) {
        return false;
    }

    // Use the equals method we defined in CustomAny
    return a.equals(b);
}

CustomAny Interpreter::evaluate(shared_ptr<Expr> expr) {
    expr->accept(*this);
    return result;
}

bool Interpreter::isTruthy(CustomAny val) {
    if (val.isNull())
        return false;
    if (val.is<bool>()) {
        return val.get<bool>();
    }
    return true;
}

CustomAny Interpreter::visitLiteralExpr(Literal& expr) {
    ;
    return expr.value;
}

CustomAny Interpreter::visitGroupingExpr(Grouping& expr) {
    return evaluate(expr.expression);
}

CustomAny Interpreter::visitUnaryExpr(Unary& expr) {
    CustomAny right = expr.right;

    switch (expr.operatorToken.type) {
    case TokenType::MINUS:
        if (right.is<double>()) {
            return -right.get<double>();
        } else if (right.is<int>()) {
            return -static_cast<double>(right.get<int>());
        } else {
            // Handle error or throw an exception
            throw std::runtime_error("Operand must be a number");
        }
    case TokenType::BANG:
        return !isTruthy(right);
    default:
        break;
    }

    return NULL;
}

CustomAny Interpreter::visitBinaryExpr(Binary& expr) {
    CustomAny right = expr.right;
    CustomAny left = expr.left;

    switch (expr.operatorToken.type) {
    case TokenType::MINUS:
        return left.toDouble() - right.toDouble();
    case TokenType::SLASH:
        return left.toDouble() / right.toDouble();
    case TokenType::STAR:
        return left.toDouble() * right.toDouble();
    case TokenType::PLUS:
        if (right.is<double>() && left.is<double>()) {
            return right.get<double>() + left.get<double>();
        }
        if (right.is<string>() && left.is<string>()) {
            return right.toString() + left.toString();
        }
    case TokenType::GREATER:
        return left.toDouble() > right.toDouble();
    case TokenType::GREATER_EQUAL:
        return left.toDouble() >= right.toDouble();
    case TokenType::LESS:
        return left.toDouble() < right.toDouble();
    case TokenType::LESS_EQUAL:
        return left.toDouble() <= right.toDouble();
    case TokenType::BANG_EQUAL:
        return !isEqual(left, right);
    case TokenType::EQUAL_EQUAL:
        return isEqual(left, right);

    default:
        break;
    }

    return NULL;
}
