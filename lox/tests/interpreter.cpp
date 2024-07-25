#include "../interpreter/interpreter.hpp"
#include <memory>
#include "../AST/Expr.h"
#include "../parser/parser.h"
#include "../scanner/scanner.h"
#include "doctest.h"

CustomAny interpretString(const std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    Parser parser(tokens);
    std::shared_ptr<Expr> expr = parser.parse();
    Interpreter interpreter;
    return interpreter.interprete(expr);
}

TEST_CASE("Interpreter evaluates literal expressions") {
    SUBCASE("Number literal") {
        CustomAny result = interpretString("42");
        CHECK(result.is<double>());
        CHECK(result.get<double>() == 42.0);
    }

    SUBCASE("String literal") {
        CustomAny result = interpretString("\"Hello, World!\"");
        CHECK(result.is<std::string>());
        CHECK(result.get<std::string>() == "Hello, World!");
    }

    SUBCASE("Boolean literals") {
        CHECK(interpretString("true").get<bool>() == true);
        CHECK(interpretString("false").get<bool>() == false);
    }

    SUBCASE("Nil literal") {
        CustomAny result = interpretString("nil");
        CHECK(result.isNull());
    }
}

TEST_CASE("Interpreter evaluates unary expressions") {
    SUBCASE("Negation") {
        CustomAny result = interpretString("-5");
        CHECK(result.is<double>());
        CHECK(result.get<double>() == -5.0);
    }

    SUBCASE("Logical not") {
        CHECK(interpretString("!true").get<bool>() == false);
        CHECK(interpretString("!false").get<bool>() == true);
    }
}

TEST_CASE("Interpreter evaluates binary expressions") {
    SUBCASE("Arithmetic operations") {
        CHECK(interpretString("2 + 3").get<double>() == 5.0);
        CHECK(interpretString("5 - 3").get<double>() == 2.0);
        CHECK(interpretString("2 * 3").get<double>() == 6.0);
        CHECK(interpretString("6 / 3").get<double>() == 2.0);
    }

    SUBCASE("Comparison operations") {
        CHECK(interpretString("2 < 3").get<bool>() == true);
        CHECK(interpretString("3 > 2").get<bool>() == true);
        CHECK(interpretString("2 <= 2").get<bool>() == true);
        CHECK(interpretString("2 >= 2").get<bool>() == true);
        CHECK(interpretString("2 == 2").get<bool>() == true);
        CHECK(interpretString("2 != 3").get<bool>() == true);
    }

    SUBCASE("Logical operations") {
        CHECK(interpretString("true and true").get<bool>() == true);
        CHECK(interpretString("true and false").get<bool>() == false);
        CHECK(interpretString("true or false").get<bool>() == true);
        CHECK(interpretString("false or false").get<bool>() == false);
    }
}

TEST_CASE("Interpreter handles grouping") {
    CustomAny result = interpretString("(2 + 3) * 4");
    CHECK(result.is<double>());
    CHECK(result.get<double>() == 20.0);
}

TEST_CASE("Interpreter handles complex expressions") {
    CustomAny result = interpretString("2 * (3 + 4) - 5 / (1 + 1)");
    CHECK(result.is<double>());
    CHECK(result.get<double>() == 12.5);
}

// TEST_CASE("Interpreter handles variable declarations and assignments") {
//     Interpreter interpreter;
//
//     SUBCASE("Variable declaration") {
//         interpreter.interprete("var x = 10;");
//         CustomAny result = interpreter.interprete("x");
//         CHECK(result.is<double>());
//         CHECK(result.get<double>() == 10.0);
//     }
//
//     SUBCASE("Variable assignment") {
//         interpreter.interpret("var y = 5;");
//         interpreter.interpret("y = 15;");
//         CustomAny result = interpreter.interpret("y");
//         CHECK(result.is<double>());
//         CHECK(result.get<double>() == 15.0);
//     }
// }

// TEST_CASE("Interpreter executes control flow statements") {
//     Interpreter interpreter;
//
//     SUBCASE("If statement") {
//         interpreter.interpret(R"(
//             var x = 10;
//             if (x > 5) {
//                 x = 20;
//             } else {
//                 x = 0;
//             }
//         )");
//         CustomAny result = interpreter.interpret("x");
//         CHECK(result.is<double>());
//         CHECK(result.get<double>() == 20.0);
//     }
//
//     SUBCASE("While loop") {
//         interpreter.interpret(R"(
//             var x = 0;
//             while (x < 5) {
//                 x = x + 1;
//             }
//         )");
//         CustomAny result = interpreter.interpret("x");
//         CHECK(result.is<double>());
//         CHECK(result.get<double>() == 5.0);
//     }
// }
//
// TEST_CASE("Interpreter handles function declarations and calls") {
//     Interpreter interpreter;
//
//     interpreter.interpret(R"(
//         fun add(a, b) {
//             return a + b;
//         }
//     )");
//
//     CustomAny result = interpreter.interpret("add(3, 4)");
//     CHECK(result.is<double>());
//     CHECK(result.get<double>() == 7.0);
// }
