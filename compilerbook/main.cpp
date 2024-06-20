#include <cstdio>
#include <iostream>
#include "token.h"

extern FILE* yyin;
extern token_t yylex();
extern char* yytext;

int main() {
    yyin = fopen(("compile_commands.json"), "r");
    if (!yyin) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    while (true) {
        token_t t = yylex();
        if (t == TOKEN_EOF)
            break;
        std::cout << "token: " << t << " text: " << yytext << std::endl;
    }
}
