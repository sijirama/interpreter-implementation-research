#include "scanner.h"
#include "../error/error.h"

using namespace std;
void Scanner::scanToken() {

    char c = advance();

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
    default:
        error(line, "Unexpected character");
        break;
    }
}

Scanner::Scanner(string source) : source(source) {}


bool Scanner::isAtEnd() {
    bool ans = current >= static_cast<int>(source.length());
    return ans;
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }

void Scanner::addToken(TokenType type, string literal) {
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
