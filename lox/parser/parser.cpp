#include "parser.h"
#include <vector>

Token Parser::advance() {

    // go to the next token by incrementing the current index

    if (!isAtEnd())
        incrementCurrent();
    return previous();
}

bool Parser::check(TokenType type) {

    // check if the currrent type is the if the given type
    // peek basically just checks the current token, so this functions just
    // checks if the token thype you passed in is the same as the current one

    if (isAtEnd())
        return false;
    return peek().type == type;
}

bool Parser::matchImpl(const vector<TokenType>& tokens) {

    // implementation of .match() so as to take numerous arguments
    // c++ probably has a better way of doing this, this was the solution that
    // just came to mind;

    for (auto type : tokens) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

Expr* Parser::equality() {
    Expr* expr = comparison();

    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        Token op = previous();
        Expr* right = comparison();
        expr = new Binary(expr, op, right);
    }

    return expr;
}
