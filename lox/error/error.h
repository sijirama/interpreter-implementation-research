// error handling i think

#include <string>
#include "../token/token.h"

void error(int line, std::string message);

void LoxError(Token token, std::string message);
