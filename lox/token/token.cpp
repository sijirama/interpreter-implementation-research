#include "token.h"
#include <any>
#include <string>

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::toString() {
    std::string literalStr = "unknown";

    if (literal.type() == typeid(std::string)) {
        literalStr = std::any_cast<std::string>(literal);
    } else if (literal.type() == typeid(double)) {
        literalStr = std::to_string(std::any_cast<double>(literal));
    } else if (literal.type() == typeid(bool)) {
        literalStr = std::any_cast<bool>(literal) ? "true" : "false";
    } else if (literal.type() == typeid(std::nullptr_t)) {
        literalStr = "null";
    }

    return std::to_string(static_cast<int>(type)) + " " + lexeme;
    // + " " +
    //    literalStr;
}

// std::string Token::toString() {
//     return std::to_string(static_cast<int>(type)) + " " + lexeme;
//     +" ";
// }
