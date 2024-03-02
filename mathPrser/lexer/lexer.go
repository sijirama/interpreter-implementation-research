package lexer

import (
	"fmt"
	"mathParser/token"
	"strconv"
	"strings"
)

var NumberList = []rune{'.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}

type Lexer struct {
	tokens   []token.Token // tokens
	input    string        // input string
	position int           // current position
	char     byte          // current character
}

func NewLexer(input string) *Lexer {
	lexer := &Lexer{input: input, position: 0}
	if len(lexer.input) > 0 {
		lexer.char = lexer.input[lexer.position]
	} else {
		lexer.char = token.NULL
	}
	return lexer
}

func (L *Lexer) GenerateNumber() *token.Token {
	decimal_count := 0 // decimal fucking count
	var sb strings.Builder

	for Contains(NumberList, rune(L.char)) {
		if string(L.char) == "." && decimal_count <= 1 {
			decimal_count++
		}

		if sb.Len() < 1 && decimal_count > 0 {
			sb.WriteString("0")
		}
		sb.WriteString(string(L.char))
		L.GetNext()
	}
	str := sb.String()
	f, err := strconv.ParseFloat(str, 64)
	if err != nil {
		fmt.Println("Error:", err)
		return nil
	}
	str = strconv.FormatFloat(f, 'f', decimal_count, 64)
	return token.NewToken(token.NUMBER, str) //WTAF: are you doing siji, this is insane code
}

func (L *Lexer) GetNext() {
	L.position++
	if L.position < len(L.input) {
		L.char = L.input[L.position]
	} else {
		L.char = token.NULL
	}
}

func (L *Lexer) GetTokens() []token.Token {
	for {
		if L.char == ' ' || L.char == '\t' {
			// Skip empty space
			L.GetNext()
			continue
		}
		if Contains(NumberList, rune(L.char)) {
			number := L.GenerateNumber()
			L.tokens = append(L.tokens, *number)
		}
		if L.char == token.NULL {
			eofToken := token.NewToken(token.EOF, "")
			L.tokens = append(L.tokens, *eofToken) //INFO: dereferece the pointer
			break
		}
		//L.GetNext()
	}
	return L.tokens
}

func (L *Lexer) ToString() string {
	var sb strings.Builder

	for _, token := range L.tokens {
		sb.WriteString(token.ToString())
		sb.WriteString(" ") // Add separator between tokens
	}

	return sb.String()
}

func Contains(list []rune, char rune) bool {
	for _, c := range list {
		if c == char {
			return true
		}
	}
	return false
}
