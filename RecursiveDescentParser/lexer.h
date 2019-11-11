/*
	This header file declares the `Token` and `Lexer` classes.
	The `Lexer` class parses a given string, by use of the 
	`nextToken` method. The `Token` class is used to bundle token information
	into a single object.


	Implementation is probably inefficient, specifically that of the `Token` class. 
*/

#include <iostream> // for using std::string

#pragma once

namespace lexer {

	class Token
	{
	public:
		// the default class constructor is here so a variable of type `Token` can be initialized without values
		Token();
		Token(int type, std::string text); // the class constructor.
		int type; // type is an int, appropiate constants are defined in the definition file.
		std::string text; // this is the input-text that evaluated to this token.
		std::string toString(); // evaluates the token text and type to a string.
	};

	class Lexer
	{
	public:
		Lexer(std::string input); // the class constructor.
		void match(char x); // asserts that (c == x), and increments the cursor.
		
		/* `nextToken` returns the next token in the stream.
		should be called repeatedly to tokenize the entire input */
		Token nextToken(); 

	private:
		std::string input; // the input string
		unsigned p = 0;    // this is the cursor
		char c;            // this is the character at cursor position
		void consume();    // moves the cursor one space
		void WS();         // moves the cursor past any whitespace
		bool isLETTER();   // checks if `c` is a letter

		Token NAME();      // returns a token of type tNAME
	};
}
