#include "token.h"
#include <any>
#include <string>

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::toString() {
    return std::to_string(static_cast<int>(type)) + " " + lexeme + " " +
           (std::any_cast<std::string>(literal));
}
