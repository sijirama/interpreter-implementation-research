#include <string>
#include <vector>
#include "../AST/print.h"
#include "../parser/parser.h"
#include "../scanner/scanner.h"
#include "doctest.h"

using namespace std;
TEST_CASE("Parser works") {
    std::string source = "print language";
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();

    cout << "Tokens:" << endl;
    for (Token& token : tokens) {
        cout << token.toString() << endl;
    }

    Parser parser(tokens);
    auto expr = parser.parse();

    REQUIRE(expr != nullptr);

    if (expr) {
        ASTPrinter printer;
        auto value = printer.print(*expr);
        cout << "Parsed expression: " << value << endl;
        CHECK(value == "print statement");
    } else {
        cout << "Failed to parse expression" << endl;
    }
}

TEST_CASE("Parser works") {
    std::string source = R"(
        // this won't be scanned in the scanner

        /*
        this won't be scanned in the scanner

        */
        print 44;

        var language = "lox";
        var region = "africa";

        print language

        fun addPair(a, b) {
            return a + b;
        }
    )";
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();

    cout << "============================================" << endl;
    for (Token token : tokens) {
        cout << token.toString() << endl;
    }
    cout << "============================================" << endl;
    Parser parser = Parser(tokens);
    auto expr = parser.parse();
    ASTPrinter printer;
    auto value = printer.print(*expr);
    cout << value << endl;
}
