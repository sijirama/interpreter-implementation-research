#include "error.h"
#include <iostream>
#include <string>

void report(int line, std::string where, std::string message) {
    std::cerr << "[line ]" << line << " ] Error " << where << " : " << message
              << std::endl;
}

void error(int line, std::string message) { report(line, "", message); }

void LoxError(Token token, std::string message) {
    if (token.type == TokenType::END_OF_FILE) {
        report(token.line, " at the end ", message);
    } else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
};
