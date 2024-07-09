- notes i've been taking during development

expression  → literal
            | unary
            | binary
            | grouping ;

literal → NUMBER | STRING | "true" | "false" | "nil" ;

grouping → "(" expression ")" ;

unary → ( "-" | "!" ) expression ;

binary → expression operator expression ;

operator → "==" | "!=" | "<" | "<=" | ">" | ">=" | "*" | "/" | "+" | "-";

- the funny thing is that i can ad to this grammar and do a ternary expression

ternary → expression operator expression operator expression ;

- assignment, add ternary to lox right after whenever you can
