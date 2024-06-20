%{
#include "token.h"
%}

DIGIT [0-9]
LETTER [a-zA-Z]
HEXDIGIT [0-9a-fA-F]
ESCAPE \\([\"\\/bfnrt] | u{HEXDIGIT}{4})

%%

"{"         { return TOKEN_LBRACE; }
"}"         { return TOKEN_RBRACE; }
"["         { return TOKEN_LBRACKET; }
"]"         { return TOKEN_RBRACKET; }
","         { return TOKEN_COMMA; }
":"         { return TOKEN_COLON; }
\"([^\"\\\n]|{ESCAPE})*\"  { return TOKEN_STRING; }
-?{DIGIT}+(\.{DIGIT}+)?([eE][+-]?{DIGIT}+)?  { return TOKEN_NUMBER; }
true        { return TOKEN_TRUE; }
false       { return TOKEN_FALSE; }
null        { return TOKEN_NULL; }
[ \t\n\r]+  { /* Ignore whitespace */ }
.           { return TOKEN_ERROR; }
<<EOF>>     { return TOKEN_EOF; }

%%

int yywrap() { return 1; }

