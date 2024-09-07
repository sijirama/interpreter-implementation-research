

#include <cassert>

#include "../Lox/Expr/GroupingExpr.h"

namespace Lox {
    GroupingExpr::GroupingExpr(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {
        assert(this->expr != nullptr);
    }

    std::any GroupingExpr::accept(ExprVisitor<std::any>& visitor) const {
        return visitor.visitGroupingExpr(*this);
    }

}  // namespace Lox
