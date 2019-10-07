// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
// use it to tokenize and output a specified file
// the program must be invoked with a filename provided

#include <iostream> // for using string, cout, cerr, endl
#include <fstream> // for file reading (ifstream) and related errors (strerror_s)
#include "Lexer.h"

using namespace std; // so I don't have to type std:: all over the place


extern const int tEOF; // this constant is defined in lexer.cpp, it is used here to check for EOF

int main(int argc, char* argv[])
{
	// check that a filename was specified as a command line arguement, else terminate execution
	if (argc == 1) {
		cerr << "No file name supplied" << endl;
		exit(0);   // call system to stop
	}

	// attempt to open the specified file
	ifstream inFile;
	inFile.open(argv[1]);

	// check that the file was opened, else return error and terminate execution
	if (!inFile) {
		char e[100];
		strerror_s(e, errno);
		cerr << "Unable to open file " << argv[1] << ": "<< e << endl;
		exit(0);   // call system to stop
	}

	inFile >> std::noskipws; // this ensures that whitespace is not skipped.

	// declare `c` for file input streaming. used to construct `inputString`
	char c;
	// declare `inputString`. used in initializing the `RecursiveDescentLexer`
	string inputString;

	// stream file and build `inputString`
	inFile >> c;
	do {
		inputString.push_back(c);
	} while (inFile >> c);
	inFile.close(); // close file
	
	// initialize lexer
	lexer::RecursiveDescentLexer L = lexer::RecursiveDescentLexer(inputString);
	// initialize token variable
	lexer::Token t;
	// parse and output a string representation of all tokens
	do {
		t = L.nextToken();
		cout << t.toString() << endl;
	} while (t.type != tEOF);
}
