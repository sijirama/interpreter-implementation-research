#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "../AST/Expr.h"
#include "../error/error.h"

class Parser {
  private:
    const vector<Token> tokens;
    int current = 0;

    class ParseError : runtime_error {
      public:
        ParseError() : std::runtime_error("Parse error"){};
        explicit ParseError(const std::string& message)
            : std::runtime_error(message) {}
    };

    ParseError Error(Token token, string message) {
        LoxError(token, message);
        return ParseError("Parse Error found");
    }

  public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}

    shared_ptr<Expr> parse();
    void synchronize();

    // utils
    template <typename... Args>

    bool match(Args... tokens) {
        return matchImpl({tokens...});
    }

    bool check(TokenType token);

    void incrementCurrent() { current++; }

    Token advance();

    bool matchImpl(const vector<TokenType>& types);

    bool isAtEnd() { return peek().type == TokenType::END_OF_FILE; }

    Token peek() { return tokens[current]; }

    Token previous() { return tokens[current - 1]; }

    Token consume(TokenType, string);

    // main stuff

    shared_ptr<Expr> expression();
    shared_ptr<Expr> equality();
    shared_ptr<Expr> comparison();
    shared_ptr<Expr> term();
    shared_ptr<Expr> factor();
    shared_ptr<Expr> unary();
    shared_ptr<Expr> primary();
};
