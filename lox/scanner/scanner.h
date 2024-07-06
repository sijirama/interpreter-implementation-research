
#include <string>
#include <vector>
#include "../token/token.h"

class Scanner {
  private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

  public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::string literal);
};
