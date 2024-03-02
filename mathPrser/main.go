package main

import (
	"fmt"
	"mathParser/lexer"
	"os"
	"strings"
)

func main() {
	fmt.Println("Welcome to Tokode, a nifty and easy to use math interpreter.")

	for {
		fmt.Print(">> ")
		var input string
		fmt.Scanln(&input)

		if strings.TrimSpace(input) == "exit()" || strings.TrimSpace(input) == "exit" {
			break
		}

		lexer := lexer.NewLexer(input)
		tokens := lexer.GetTokens()

		// Here, you can evaluate the user input and perform actions based on it.
		fmt.Printf(">> %s\n", lexer.ToString())
		fmt.Println(tokens)

	}

	fmt.Println("Goodbye!")
	os.Exit(0)
}
