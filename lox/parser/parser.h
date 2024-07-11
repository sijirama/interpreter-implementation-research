#include <memory>
#include <vector>
#include "../AST/Expr.h"

class Parser {
  private:
    const vector<Token> tokens;
    int current = 0;

  public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}

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

    void consume();

    // main stuff

    shared_ptr<Expr> expression() { return equality(); }
    shared_ptr<Expr> equality();
    shared_ptr<Expr> comparison();
    shared_ptr<Expr> term();
    shared_ptr<Expr> factor();
    shared_ptr<Expr> unary();
    shared_ptr<Expr> primary();
};
