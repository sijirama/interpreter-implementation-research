#include <any>
#include <string>
#include "../utils/util.h"

enum class TokenType {
    LEFT_PAREN, // Single-character tokens.
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    BANG, // One or two character tokens.
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    IDENTIFIER, // Literals.
    STRING,
    NUMBER,
    AND, // Keywords.
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,
    END_OF_FILE,
};

class Token {
  private:
    TokenType type;
    // std::string lexeme;
    std::string lexeme;
    std::any literal;
    int line;

  public:
    Token(TokenType type, std::string lexeme, std::any literal, int line);
    std::string toString();
};
