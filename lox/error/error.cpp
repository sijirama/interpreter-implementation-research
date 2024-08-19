
#include "error.h"
using namespace std;

void report(int line, const std::string& where, const std::string& message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message
              << std::endl;
}

void error(int line, const std::string& message) { report(line, "", message); }

void LoxError(const Token& token, const std::string& message) {
    if (token.type == TokenType::END_OF_FILE) {
        report(token.line, " at end", message);
    } else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void runtimeErrorReporter(const RuntimeError& rerror) {
    std::cerr << rerror.getMessage() << std::endl;
}
