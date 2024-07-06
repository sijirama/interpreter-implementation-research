
#include <string>
#include <vector>
#include "../token/token.h"

class Scanner {
  private:
    std::string source;

  public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();
};
