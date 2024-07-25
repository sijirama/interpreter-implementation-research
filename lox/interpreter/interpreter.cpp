#include "interpreter.hpp"
#include <cstddef>
#include <memory>
#include <vector>
#include "../error/error.h"

CustomAny Interpreter::interprete(shared_ptr<Expr> expression) {
    try {
        CustomAny value = evaluate(expression);
        return value;
    } catch (RuntimeError error) {
        runtimeErrorReporter(error);
        return NULL;
    }
}

std::string Interpreter::stringify(const CustomAny& object) {
    if (object.isNull())
        return "nil";

    if (object.is<double>()) {
        std::string text = object.toString();
        if (text.length() > 2 && text.substr(text.length() - 2) == ".0") {
            text = text.substr(0, text.length() - 2);
        }
        return text;
    }

    return object.toString();
}

template <typename... Args>
void Interpreter::checkNumberOperands(const Token& op, const Args&... args) {
    // check if the operands in an expr is a number
    std::vector<CustomAny> operands = {args...};
    for (const auto& operand : operands) {
        if (!operand.is<double>() && !operand.is<int>()) {
            throw RuntimeError(op, "Operands must be numbers.");
        }
    }
}
void Interpreter::checkNumberOperand(Token op, CustomAny operand) {
    // check if the operand in an expr is a number
    if (operand.is<double>())
        return;
    throw new RuntimeError(op, "Operand must be a number");
}

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
    return expr->accept(*this);
}

bool Interpreter::isTruthy(CustomAny val) {
    if (val.isNull())
        return false;
    if (val.is<bool>()) {
        return val.get<bool>();
    }
    return true;
}

CustomAny Interpreter::visitLiteralExpr(const Literal& expr) {
    ;
    return expr.value;
}

CustomAny Interpreter::visitGroupingExpr(const Grouping& expr) {
    return evaluate(expr.expression);
}

CustomAny Interpreter::visitUnaryExpr(const Unary& expr) {
    CustomAny right = expr.right;

    switch (expr.operatorToken.type) {
    case TokenType::MINUS:
        checkNumberOperand(expr.operatorToken, right);
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

CustomAny Interpreter::visitBinaryExpr(const Binary& expr) {
    CustomAny right = expr.right;
    CustomAny left = expr.left;

    switch (expr.operatorToken.type) {
    case TokenType::MINUS:
        checkNumberOperands(expr.operatorToken, left, right);
        return left.toDouble() - right.toDouble();
    case TokenType::SLASH:
        checkNumberOperands(expr.operatorToken, left, right);
        return left.toDouble() / right.toDouble();
    case TokenType::STAR:
        checkNumberOperands(expr.operatorToken, left, right);
        return left.toDouble() * right.toDouble();
    case TokenType::PLUS:
        if (right.is<double>() && left.is<double>()) {
            return right.get<double>() + left.get<double>();
        }
        if (right.is<string>() && left.is<string>()) {
            return right.toString() + left.toString();
        } else {
            throw new RuntimeError(
                expr.operatorToken,
                "Operands must be two numbers or two strings.");
        }
    case TokenType::GREATER:
        checkNumberOperands(expr.operatorToken, left, right);
        return left.toDouble() > right.toDouble();
    case TokenType::GREATER_EQUAL:
        checkNumberOperands(expr.operatorToken, left, right);
        return left.toDouble() >= right.toDouble();
    case TokenType::LESS:
        checkNumberOperands(expr.operatorToken, left, right);
        return left.toDouble() < right.toDouble();
    case TokenType::LESS_EQUAL:
        checkNumberOperands(expr.operatorToken, left, right);
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
