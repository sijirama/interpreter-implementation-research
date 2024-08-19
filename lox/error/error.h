
#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "../token/token.h"

using namespace std;

class RuntimeError : public std::runtime_error {
  private:
    Token token;

  public:
    RuntimeError(Token token, const std::string& message)
        : std::runtime_error(message), token(token) {}

    std::string getMessage() const { return what(); }
};

void error(int line, const std::string& message);
void LoxError(const Token& token, const std::string& message);
void runtimeErrorReporter(const RuntimeError& rerror);
