#include "parser.h"
#include <memory>
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

void Parser::synchronize() {
    advance();
    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON)
            return;

        switch (peek().type) {
        case TokenType::CLASS:
        case TokenType::FUN:
        case TokenType::VAR:
        case TokenType::FOR:
        case TokenType::IF:
        case TokenType::WHILE:
        case TokenType::PRINT:
        case TokenType::RETURN:
            return;
        default:
            continue; // WARN: this can be extremely wrong, just keeping this
                      // here incase to pinpoint
        }

        advance();
    }
}

shared_ptr<Expr> Parser::parse() {
    try {
        // For now, let's just try to parse a single expression
        return expression();
    } catch (const ParseError& error) {
        // std::cerr << "Parse error: " << error.what() << std::endl;
        return nullptr;
    }
}

shared_ptr<Expr> Parser::expression() {
    if (match(TokenType::PRINT)) {
        return make_shared<Literal>("print statement");
    };
    return equality();
}

shared_ptr<Expr> Parser::equality() {
    shared_ptr<Expr> expr = comparison();

    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        Token op = previous();
        shared_ptr<Expr> right = comparison();
        expr = make_shared<Binary>(expr, op, right);
    }

    return expr;
}

shared_ptr<Expr> Parser::comparison() {
    shared_ptr<Expr> expr = term();

    while (match(TokenType::LESS, TokenType::LESS_EQUAL, TokenType::GREATER,
                 TokenType::GREATER_EQUAL)) {
        Token op = previous();
        shared_ptr<Expr> right = term();
        expr = make_shared<Binary>(expr, op, right);
    }

    return expr;
}

shared_ptr<Expr> Parser::term() {
    shared_ptr<Expr> expr = factor();

    while (match(TokenType::MINUS, TokenType::PLUS)) {
        Token op = previous();
        shared_ptr<Expr> right = factor();
        expr = make_shared<Binary>(expr, op, right);
    }

    return expr;
}

shared_ptr<Expr> Parser::factor() {
    shared_ptr<Expr> expr = unary();
    if (match(TokenType::SLASH, TokenType::STAR)) {
        Token op = previous();
        shared_ptr<Expr> right = unary();
        expr = make_shared<Binary>(expr, op, right);
    }
    return expr;
}

shared_ptr<Expr> Parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
        Token op = previous();
        shared_ptr<Expr> right = unary();
        return make_shared<Unary>(op, right);
    }
    return primary();
}

shared_ptr<Expr> Parser::primary() {
    if (match(TokenType::FALSE))
        return make_shared<Literal>(false);
    if (match(TokenType::TRUE))
        return make_shared<Literal>(true);
    if (match(TokenType::NIL))
        return make_shared<Literal>(nullptr);

    if (match(TokenType::NUMBER, TokenType::STRING)) {
        return make_shared<Literal>(previous().literal);
    }
    if (match(TokenType::LEFT_PAREN)) {
        shared_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Exprect ')' after expression");
        return make_shared<Grouping>(expr);
    }

    throw Error(peek(), "Expect expression");
}

Token Parser::consume(TokenType type, string message) {
    if (check(type))
        return advance();
    throw Error(peek(), message);
}
