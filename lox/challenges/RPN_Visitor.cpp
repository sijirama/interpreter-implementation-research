#include "../AST/Expr.h"

class RPNPrinter : public Expr::Visitor {
  private:
    std::string result;

  public:
    std::string print(Expr& expr) {
        expr.accept(*this);
        return result;
    }
};
