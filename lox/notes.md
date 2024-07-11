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

expression  → equality ;
equality    → comparison ( ( "!=" | "==" ) comparison )* ;
comparison  → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term    → factor ( ( "-" | "+" ) factor )* ;
factor  → unary ( ( "/" | "*" ) unary )* ;
unary
        → ( "!" | "-" ) unary
        | primary ;
primary
        → NUMBER | STRING | "true" | "false" | "nil"
        | "(" expression ")" ;
