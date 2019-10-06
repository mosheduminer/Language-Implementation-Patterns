#include <iostream>

#pragma once

namespace lexer {

	class Token
	{
	public:
		int type;
		std::string text;
		Token(int type, std::string text);
		std::string toString();
	};

	class RecursiveDescentLexer
	{
	public:
		RecursiveDescentLexer(std::string input);
		void match(char x);
		Token nextToken();

	private:
		std::string input;
		unsigned p = 0;
		char c;
		void consume();
		void WS();
		bool isLETTER();

		Token NAME();
	};
}