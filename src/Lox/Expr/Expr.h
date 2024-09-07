#pragma once

#include <any>

#include "ExprVisitor.h"

namespace Lox {
    class Expr {
        public:
            virtual ~Expr() = default;

            virtual std::any accept(ExprVisitor<std::any>& visitor) const = 0;
    };
}  // end of namespace Lox
