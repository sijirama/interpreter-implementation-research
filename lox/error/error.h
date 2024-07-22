// error handling i think

#include <stdexcept>
#include <string>
#include "../token/token.h"

class RuntimeError : runtime_error {

    Token token;

  public:
    RuntimeError(Token token, const std::string& message)
        : std::runtime_error(message), token(token) {}
};

void error(int line, std::string message);

void LoxError(Token token, std::string message);
