#include <iostream>
#include <memory>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "../AST/Expr.h"
#include "../AST/print.h"
#include "../scanner/scanner.h"
#include "doctest.h"

TEST_CASE("ASTPrinter correctly prints complex expression") {
    // Create the expression: (- 123) * (group 45.67)
    auto expression = std::make_shared<Binary>(
        std::make_shared<Unary>("-", std::make_shared<Literal>("123")), "*",
        std::make_shared<Grouping>(std::make_shared<Literal>("45.67")));

    ASTPrinter printer;
    std::string result = printer.print(*expression);

    cout << result << std::endl;
    CHECK(result == "(* (- 123) (group 45.67))");
}

TEST_CASE("ASTPrinter correctly prints simple expressions") {
    SUBCASE("Literal expression") {
        auto expr = std::make_shared<Literal>("42");
        ASTPrinter printer;
        CHECK(printer.print(*expr) == "42");
    }

    SUBCASE("Unary expression") {
        auto expr =
            std::make_shared<Unary>("-", std::make_shared<Literal>("7"));
        ASTPrinter printer;
        CHECK(printer.print(*expr) == "(- 7)");
    }

    SUBCASE("Binary expression") {
        auto expr =
            std::make_shared<Binary>(std::make_shared<Literal>("3"), "+",
                                     std::make_shared<Literal>("4"));
        ASTPrinter printer;
        CHECK(printer.print(*expr) == "(+ 3 4)");
    }

    SUBCASE("Grouping expression") {
        auto expr = std::make_shared<Grouping>(std::make_shared<Literal>("99"));
        ASTPrinter printer;
        CHECK(printer.print(*expr) == "(group 99)");
    }
}

TEST_CASE("ASTPrinter handles empty or null expressions") {
    SUBCASE("Empty literal") {
        auto expr = std::make_shared<Literal>("");
        ASTPrinter printer;
        CHECK(printer.print(*expr) == "nil");
    }

    // Add more subcases for other types if needed
}
