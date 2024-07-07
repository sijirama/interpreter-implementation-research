#include <any>
#include <map>
#include <string>
#include <vector>
#include "../error/error.h"
#include "../token/token.h"
#include "../utils/util.h"

class Scanner {
  private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;
    std::map<std::string, TokenType> keywords;

  public:
    bool match(char expected);
    Scanner(std::string source);
    std::vector<Token> scanTokens();
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::any literal);
    char peek();
    char peekNext();

    bool isDigit(char c);

    void stringLiteral();
    void numberLiteral();
    void identifier();
    void handleComment();
    bool isAlpha(char c);
    bool isAlphanumeric(char c);
};
