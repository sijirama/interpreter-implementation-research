#include <fmt/core.h>

#include <any>
#include <fstream>
#include <iostream>
#include <string>

#include "Lox/Error.h"
#include "Lox/Expr/BinaryExpr.h"
#include "Lox/Expr/Expr.h"
#include "Lox/Expr/GroupingExpr.h"
#include "Lox/Expr/LiteralExpr.h"
#include "Lox/Expr/Printer.h"
#include "Lox/Expr/UnaryExpr.h"
#include "Lox/Scanner.h"
#include "Lox/Token.h"
#include "Lox/TokenType.h"

#define LOX_VERSION "0.0.1"

void run(const std::string &source) {
    Lox::Scanner scanner{source};
    std::vector<Lox::Token> tokens = scanner.scanTokens();
    for (Lox::Token token : tokens) {
        fmt::print("{}\n", token.toString());
    };
}

void runFile(const std::string &filename) {
    std::ifstream file{filename};
    if (!file.good()) {
        // TODO: write proper error message
        fmt::print("Failed to open {}: No such file or directory\n", filename);
        return;
    }

    std::string line;
    std::string source;
    while (std::getline(file, line)) {
        source += line + "\n";
    }

    run(source);
    if (Lox::Lox::HadError) {
        exit(2);
    }
    if (Lox::Lox::HadRuntimeError) {
        exit(3);
    }
}

void runPrompt() {
    fmt::print("lox v{}\n", LOX_VERSION);

    std::string code;
    while (true) {
        fmt::print("> ");
        if (std::getline(std::cin, code)) {
            run(code);
            Lox::Lox::HadError = false;
        } else {
            fmt::print("\n");
            break;
        }
    }
}

int main(int args, char *argv[]) {
    // if (args > 2) {
    //     fmt::print("usage: lox [script]\n");
    //     exit(1);
    // } else if (args == 2) {
    //     runFile(argv[1]);
    // } else {
    //     runPrompt();
    // }
    // Create a new expression:
    //  ( -123 ) * ( 45.67 )

    std::unique_ptr<Lox::Expr> expression = std::make_unique<Lox::BinaryExpr>(
        std::make_unique<Lox::UnaryExpr>(
            Lox::Token(Lox::TokenType::Minus, "-", std::any(), 1),
            std::make_unique<Lox::LiteralExpr>(std::make_any<int>(123))),
        Lox::Token(Lox::TokenType::Star, "*", std::any(), 1),
        std::make_unique<Lox::GroupingExpr>(
            std::make_unique<Lox::LiteralExpr>(std::make_any<double>(45.67))));

    // Create an AstPrinter and print the expression
    Lox::AstPrinter printer;
    std::any result = printer.print(*expression);

    std::string final = std::any_cast<std::string>(result);

    // Output the result
    std::cout << final << std::endl;
}
