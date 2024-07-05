
#include <string>
#include <vector>
class Scanner {
  private:
    std::string source;

  public:
    Scanner(std::string source);
    std::vector<std::string> scanTokens();
};
