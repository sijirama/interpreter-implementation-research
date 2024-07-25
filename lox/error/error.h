// error handling i think
#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "../token/token.h"

using namespace std;

class RuntimeError : runtime_error {

    Token token;
    string Message;

  public:
    RuntimeError(Token token, const std::string& message)
        : std::runtime_error(message), token(token), Message(message) {}

    string getMessage() { return Message; }
};

void error(int line, std::string message);

void LoxError(Token token, std::string message);

void runtimeErrorReporter(RuntimeError rerror) {
    cerr << rerror.getMessage() << endl;
    ;
}
