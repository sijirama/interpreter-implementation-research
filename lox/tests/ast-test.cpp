#include <iostream>
#include <memory>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "../AST/Expr.h"
#include "../AST/print.h"
#include "doctest.h"

Token minusToken = Token(TokenType::MINUS, "-", "-", 10);
Token starToken = Token(TokenType::STAR, "*", "*", 10);
Token plusToken = Token(TokenType::PLUS, "+", "+", 10);

TEST_CASE("ASTPrinter works") {
    auto expr = std::make_shared<Literal>(42);
    // expr->printValue();
    //
    // string val = "4244";
    // Literal lit("4244");
    // lit.printValue();
    //
    // Literal litInt(400);
    // litInt.printValue();
    //
    // Literal litStr(std::string("Hello"));
    // litStr.printValue();

    ASTPrinter printer = {};
    auto value = printer.print(*expr);
    std::cout << value << endl;
    std::cout << minusToken.toString() << endl;
    CHECK(value == "42");
}

TEST_CASE("ASTPrinter correctly prints complex expression") {

    // Create the expression: (- 123) * (group 45.67)
    // Create the expression: (- 123) - (group 45.67)

    auto expression = std::make_shared<Binary>(
        std::make_shared<Unary>(minusToken, std::make_shared<Literal>("123")),
        starToken,
        std::make_shared<Grouping>(std::make_shared<Literal>("45.67")));

    ASTPrinter printer;
    std::string result = printer.print(*expression);

    cout << result << std::endl;
    CHECK(result == "(* (- 123) (group 45.67))");
}

TEST_CASE("ASTPrinter correctly prints simple expressions") {
    SUBCASE("Literal expression") {
        auto expr = std::make_shared<Literal>("42");
        ASTPrinter printer = {};
        auto value = printer.print(*expr);
        std::cout << value << endl;
        CHECK(value == "42");
    }

    SUBCASE("Unary expression") {
        auto expr =
            std::make_shared<Unary>(minusToken, std::make_shared<Literal>("7"));

        ASTPrinter printer;
        auto value = printer.print(*expr);
        CHECK(value == "(- 7)");
    }

    SUBCASE("Binary expression") {
        auto expr =
            std::make_shared<Binary>(std::make_shared<Literal>("3"), plusToken,
                                     std::make_shared<Literal>("4"));
        ASTPrinter printer;
        auto value = printer.print(*expr);
        std::cout << value << endl;
        CHECK(value == "(+ 3 4)");
    }

    SUBCASE("Grouping expression") {
        auto expr = std::make_shared<Grouping>(std::make_shared<Literal>("99"));
        ASTPrinter printer;
        auto value = printer.print(*expr);
        std::cout << value << endl;
        CHECK(value == "(group 99)");
    }
}

TEST_CASE("ASTPrinter handles empty or null expressions") {
    SUBCASE("Empty literal") {
        auto expr = std::make_shared<Literal>("");
        ASTPrinter printer;
        auto value = printer.print(*expr);
        std::cout << value << endl;
        CHECK(value == "nil");
    }
}
