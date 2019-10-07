/* Implementation file for "lexer.h". see there for further information */

#include <iostream>
#include "lexer.h"

using namespace std;
using namespace lexer;


// global constants representing possible token types
extern const int tINVALID = 0;
extern const int tEOF = 1;
extern const int tNAME = 2;
extern const int tCOMMA = 3;
extern const int tLBRACK = 4;
extern const int tRBRACK = 5;

// array of token names, indexed by their the corrsponding constant
string tokenNames[6] = { "n/a", "<EOF>", "NAME", "COMMA", "LBRACK", "RBRACK" };

// used instead of accessing `tokenNames` directly. Redundant, since tokenNames is not private
string getTokenName(int x) { return tokenNames[x]; }

// implementation of `Token` class constructor. Assigns type and text.
Token::Token(int type, string text) { this->type = type; this->text = text; }
// implementation of `Token` default class constructor. Assigns type tINVALID.
Token::Token() { this->type = tINVALID; this->text = "If you are seeing this, you probably did something wrong."; }

// implementation of `Token`'s `toString` method
string Token::toString() {
	if (type == EOF) {
		type = 1;
	}
	string tName = getTokenName(type);
	return "<'" + text + "', " + tName + ">";
}


// implementation of `RecursiveDescentLexer` class constructor. Assigns	`input` and initializes `c`. 
RecursiveDescentLexer::RecursiveDescentLexer(string input) {
	this->input = input;
	this->c = input.at(this->p);
}

// implementation of `RecursiveDescentLexer`'s `match` method. I haven't seen its use yet
void RecursiveDescentLexer::match(char x) {
	if (c == x) consume();
	else {
		cout << "expecting " << x << "; found " << c;
		exit(0);
	}
}

// implementation of `RecursiveDescentLexer`'s `nextToken` method
Token RecursiveDescentLexer::nextToken() {
	while (c != EOF) {
		switch (c) {
		case ' ': case '\t': case '\n': case '\r': WS(); continue;
		case ',': consume(); return Token(tCOMMA, ",");
		case '[': consume(); return Token(tLBRACK, "[");
		case ']': consume(); return Token(tRBRACK, "]");
		default:
			if (isLETTER()) return NAME();
			cout << "invalid character: " << c;
			exit(0);
		}
	} return Token(EOF, "EOF");
}

// implementation of `RecursiveDescentLexer`'s `consume` method. moves the cursor by one
void RecursiveDescentLexer::consume() {
	p++; // increment
	if (p >= input.length()) c = EOF;
	else c = input.at(p); // assign `c`
}

// implementation of `RecursiveDescentLexer`'s `WS` method. used to skip all whitespace.
void RecursiveDescentLexer::WS() {
	while (c == ' ' || c == '\t' || c == '\n' || c == '\r') consume();
}

// implementation of `RecursiveDescentLexer`'s `isLETTER` method. used to assert that `c` is a alphabetic
bool RecursiveDescentLexer::isLETTER() { return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'; }

/*
	implementation of `RecursiveDescentLexer`'s `NAME` method. used to produce a tNAME token.
	NAME : ('a'..'z'|'A'..'Z')+; // NAME is sequence of >=1 letter
*/
Token RecursiveDescentLexer::NAME() {
	string buf;
	while (isLETTER()) { buf.push_back(c); consume(); }
	return Token(tNAME, buf);
}
