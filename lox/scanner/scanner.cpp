#include "scanner.h"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
void Scanner::scanToken() {

    char c = advance(); // source[current - 1]

    switch (c) {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case '.':
        addToken(TokenType::DOT);
        break;
    case '-':
        addToken(TokenType::MINUS);
        break;
    case '+':
        addToken(TokenType::PLUS);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::LESS);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if (match('/')) {
            // so it's a comment
            while (peek() != '\n' && !isAtEnd())
                advance();
        } else {
            addToken(TokenType::SLASH);
        }

        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        line++;
        break;
    case '"':
        stringLiteral();
        break;
    case 'o':
        if (peek() == 'r') {
            addToken(TokenType::OR);
        }
        break;
    default:
        if (isDigit(c)) {
            numberLiteral();
        } else if (isAlpha(c)) {
            identifier();
        } else {
            error(line, "Unexpected character");
        }
        break;
    }
}

void Scanner::identifier() {
    while (isAlphanumeric(peek()))
        advance();
    string text = substring(source, start, current);
    TokenType type;
    if (keywords.count(text) > 0) { // check if keyword is in map
        type = keywords[text];
    } else {
        type = TokenType::IDENTIFIER;
    }
    addToken(type);
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphanumeric(char c) { return isAlpha(c) || isDigit(c); }

void Scanner::numberLiteral() {
    while (isDigit(peek()))
        advance();
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();
        while (isDigit(peek()))
            advance();
    }
    // addToken(TokenType::NUMBER, stof(source.substr(start, current)));
    addToken(TokenType::NUMBER, stof(substring(source, start, current)));
}

char Scanner::peekNext() {
    if (current + 1 >= static_cast<int>(source.length()))
        return '\0';
    return source[current + 1];
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

void Scanner::stringLiteral() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n')
            line++;
        advance();
    }
    if (isAtEnd()) {
        error(line, "Unterminated string");
        return;
    }
    advance();
    // string value = source.substr(start + 1, current - 1);
    string value = substring(source, start + 1, current - 1);
    addToken(TokenType::STRING, value);
}

char Scanner::peek() {
    if (isAtEnd())
        return '\0';
    return source[current];
}

bool Scanner::match(char expected) {
    if (isAtEnd())
        return false;
    if (source[current] != expected)
        return false;

    current++;
    return true;
}

Scanner::Scanner(string source) : source(source) {
    keywords.insert(pair<string, TokenType>("and", TokenType::AND));
    keywords.insert(pair<string, TokenType>("class", TokenType::CLASS));
    keywords.insert(pair<string, TokenType>("else", TokenType::ELSE));
    keywords.insert(pair<string, TokenType>("false", TokenType::FALSE));
    keywords.insert(pair<string, TokenType>("for", TokenType::FOR));
    keywords.insert(pair<string, TokenType>("fun", TokenType::FOR));
    keywords.insert(pair<string, TokenType>("if", TokenType::IF));
    keywords.insert(pair<string, TokenType>("nil", TokenType::NIL));
    keywords.insert(pair<string, TokenType>("or", TokenType::OR));
    keywords.insert(pair<string, TokenType>("print", TokenType::PRINT));
    keywords.insert(pair<string, TokenType>("return", TokenType::RETURN));
    keywords.insert(pair<string, TokenType>("super", TokenType::SUPER));
    keywords.insert(pair<string, TokenType>("this", TokenType::THIS));
    keywords.insert(pair<string, TokenType>("true", TokenType::TRUE));
    keywords.insert(pair<string, TokenType>("var", TokenType::VAR));
    keywords.insert(pair<string, TokenType>("while", TokenType::WHILE));
}

bool Scanner::isAtEnd() {
    ;
    return current >= static_cast<int>(source.length());
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }

void Scanner::addToken(TokenType type, any literal) {
    string text = substring(source, start, current);
    tokens.push_back(Token(type, text, literal, line));
}

char Scanner::advance() {
    current++;
    return source[current - 1];
}

vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    };
    tokens.push_back(Token(TokenType::END_OF_FILE, "", "", line));
    return tokens;
}
