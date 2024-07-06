#include "token.h"
#include <string>

Token::Token(TokenType type, std::string lexeme, std::string literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::toString() {
    return std::to_string(static_cast<int>(type)) + " " + lexeme + " " +
           literal;
}
