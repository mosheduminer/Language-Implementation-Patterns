#include <iostream>
#include "lexer.h"

using namespace std;
using namespace lexer;


extern const int tINVALID = 0;
extern const int tEOF = 1;
extern const int tNAME = 2;
extern const int tCOMMA = 3;
extern const int tLBRACK = 4;
extern const int tRBRACK = 5;

string tokenNames[6] = { "n/a", "<EOF>", "NAME", "COMMA", "LBRACK", "RBRACK" };

string getTokenName(int x) { return tokenNames[x]; }

Token::Token(int type, string text) { this->type = type; this->text = text; }
string Token::toString() {
	if (type == EOF) {
		type = 1;
	}
	string tName = getTokenName(type);
	return "<'" + text + "', " + tName + ">";
}

RecursiveDescentLexer::RecursiveDescentLexer(string input) {
	this->input = input;
	this->c = input.at(this->p);
}
void RecursiveDescentLexer::match(char x) {
	if (c == x) consume();
	else {
		cout << "expecting " << x << "; found " << c;
		throw exception("met invalid character");
	}
}

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
			throw exception("met invalid character");
		}
	} return Token(EOF, "EOF");
}
void RecursiveDescentLexer::consume() {
	p++;
	if (p >= input.length()) c = EOF;
	else c = input.at(p);
}
void RecursiveDescentLexer::WS() {
	while (c == ' ' || c == '\t' || c == '\n' || c == '\r') consume();
}
bool RecursiveDescentLexer::isLETTER() { return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'; }

/* NAME : ('a'..'z'|'A'..'Z')+; // NAME is sequence of >=1 letter */
Token RecursiveDescentLexer::NAME() {
	string buf(1, c); consume();
	while (isLETTER()) { string temp(1, c); buf.append(temp); consume(); }
	return Token(tNAME, buf);
}
