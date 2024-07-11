#include <vector>
#include "../AST/Expr.h"
#include "../token/token.h"

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

    // main stuff

    Expr* expression() { return equality(); }
    Expr* equality();
    Expr* comparison();
};
