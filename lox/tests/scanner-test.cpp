//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include <vector>
#include "../scanner/scanner.h"
#include "doctest.h"

// Helper function to check token type
void checkToken(const Token& token, TokenType expectedType,
                const std::string& expectedLexeme = "") {
    CHECK(token.type == expectedType);
    if (!expectedLexeme.empty()) {
        CHECK(token.lexeme == expectedLexeme);
    }
}

TEST_CASE("Scanner tokenizes single-character tokens correctly") {
    Scanner scanner("(){},.-+;*/");
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() == 12); // 12 tokens + EOF
    checkToken(tokens[0], TokenType::LEFT_PAREN, "(");
    checkToken(tokens[1], TokenType::RIGHT_PAREN, ")");
    checkToken(tokens[2], TokenType::LEFT_BRACE, "{");
    checkToken(tokens[3], TokenType::RIGHT_BRACE, "}");
    checkToken(tokens[4], TokenType::COMMA, ",");
    checkToken(tokens[5], TokenType::DOT, ".");
    checkToken(tokens[6], TokenType::MINUS, "-");
    checkToken(tokens[7], TokenType::PLUS, "+");
    checkToken(tokens[8], TokenType::SEMICOLON, ";");
    checkToken(tokens[9], TokenType::STAR, "*");
    checkToken(tokens[10], TokenType::SLASH, "/");
    checkToken(tokens[11], TokenType::END_OF_FILE);
}

TEST_CASE("Scanner handles comments correctly") {
    Scanner scanner("// This is a comment\n/* This is a block comment */");
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() == 1); // Only EOF token
    checkToken(tokens[0], TokenType::END_OF_FILE);
}

TEST_CASE("Scanner tokenizes string literals") {
    Scanner scanner("\"Hello, world!\"");
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() == 2); // String token + EOF
    checkToken(tokens[0], TokenType::STRING, "\"Hello, world!\"");
}

TEST_CASE("Scanner tokenizes number literals") {
    Scanner scanner("123 456.789");
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() == 3); // Two number tokens + EOF
    checkToken(tokens[0], TokenType::NUMBER, "123");
    checkToken(tokens[1], TokenType::NUMBER, "456.789");
}

TEST_CASE("Scanner tokenizes keywords and identifiers") {
    Scanner scanner("var language = \"lox\";");
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() == 6); // var, language, =, "lox", ;, EOF
    checkToken(tokens[0], TokenType::VAR, "var");
    checkToken(tokens[1], TokenType::IDENTIFIER, "language");
    checkToken(tokens[2], TokenType::EQUAL, "=");
    checkToken(tokens[3], TokenType::STRING, "\"lox\"");
    checkToken(tokens[4], TokenType::SEMICOLON, ";");
    checkToken(tokens[5], TokenType::END_OF_FILE);
}

TEST_CASE("Scanner handles the example code correctly") {
    std::string example_code = R"(
// this won't be scanned in the scanner
/*
this won't be scanned in the scanner
*/
var language = "lox";
print language;
fun addPair(a, b) {
    return a + b;
}
fun identity(a) {
    return a;
}
print identity(addPair)(1, 2);
if (condition) {
    print "yes";
} else {
    print "no";
}
)";

    Scanner scanner(example_code);
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() > 1); // Ensure we have tokens besides EOF
    checkToken(tokens[0], TokenType::VAR, "var");
    checkToken(tokens[1], TokenType::IDENTIFIER, "language");
    checkToken(tokens[2], TokenType::EQUAL, "=");
    checkToken(tokens[3], TokenType::STRING, "\"lox\"");
    // Add more checks later
}

TEST_CASE("Scanner handles operators correctly") {
    Scanner scanner("! != = == > >= < <=");
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() == 9); // 8 operators + EOF
    checkToken(tokens[0], TokenType::BANG, "!");
    checkToken(tokens[1], TokenType::BANG_EQUAL, "!=");
    checkToken(tokens[2], TokenType::EQUAL, "=");
    checkToken(tokens[3], TokenType::EQUAL_EQUAL, "==");
    checkToken(tokens[4], TokenType::GREATER, ">");
    checkToken(tokens[5], TokenType::GREATER_EQUAL, ">=");
    checkToken(tokens[6], TokenType::LESS, "<");
    checkToken(tokens[7], TokenType::LESS_EQUAL, "<=");
    checkToken(tokens[8], TokenType::END_OF_FILE);
}

TEST_CASE("Scanner recognizes all keywords") {
    Scanner scanner("and class else false fun for if nil or print return super "
                    "this true var while");
    std::vector<Token> tokens = scanner.scanTokens();

    CHECK(tokens.size() == 17); // 16 keywords + EOF
    checkToken(tokens[0], TokenType::AND, "and");
    checkToken(tokens[1], TokenType::CLASS, "class");
    checkToken(tokens[2], TokenType::ELSE, "else");
    checkToken(tokens[3], TokenType::FALSE, "false");
    checkToken(tokens[4], TokenType::FUN, "fun");
    checkToken(tokens[5], TokenType::FOR, "for");
    checkToken(tokens[6], TokenType::IF, "if");
    checkToken(tokens[7], TokenType::NIL, "nil");
    checkToken(tokens[8], TokenType::OR, "or");
    checkToken(tokens[9], TokenType::PRINT, "print");
    checkToken(tokens[10], TokenType::RETURN, "return");
    checkToken(tokens[11], TokenType::SUPER, "super");
    checkToken(tokens[12], TokenType::THIS, "this");
    checkToken(tokens[13], TokenType::TRUE, "true");
    checkToken(tokens[14], TokenType::VAR, "var");
    checkToken(tokens[15], TokenType::WHILE, "while");
}
