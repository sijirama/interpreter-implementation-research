#include "scanner.h"
#include <cctype>
#include <string>

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
        } else {
            error(line, "Unexpected character");
        }
        break;
    }
}

void Scanner::identifier() {
    if (isAlphanumeric(peek()))
        advance();

    addToken(TokenType::IDENTIFIER);
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
    addToken(TokenType::NUMBER, stof(source.substr(start, current)));
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
    string value = source.substr(start + 1, current - 1);
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

Scanner::Scanner(string source) : source(source) {}

bool Scanner::isAtEnd() {
    bool ans = current >= static_cast<int>(source.length());
    return ans;
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }

void Scanner::addToken(TokenType type, any literal) {
    string text = source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line));
}

char Scanner::advance() {
    current++;
    return source[current - 1];
}

vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
    };
    tokens.push_back(Token(TokenType::END_OF_FILE, "", "", line));
    return tokens;
}
