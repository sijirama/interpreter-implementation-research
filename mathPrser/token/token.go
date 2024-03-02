package token

import "fmt"

const (
	EOF      = "EOF"    // "EOF"
	NUMBER   = "NUMBER" // 1343456
	PLUS     = "+"      // addition
	MINUS    = "-"      // subtraction
	MULTIPLY = "*"      // multiplication
	DIVISION = "/"      // division
	LPAREN   = "("      // separator
	RPAREN   = ")"      // separator

	NULL = '\x00'
)

type TokenType string

type Token struct {
	Type  TokenType
	Value string
}

func (T Token) ToString() string {
	return fmt.Sprintf("%v : %s", T.Type, T.Value)
}

func NewToken(tokenType TokenType, value string) *Token {
	return &Token{Type: tokenType, Value: value}
}
