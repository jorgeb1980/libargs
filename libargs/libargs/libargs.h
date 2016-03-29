#pragma once

#include <list>
#include <set>
#include <tchar.h>

using namespace std;

// Simple macro to tell if some option is written twice
#define CONTAINS(x, y) (std::find(x.begin(), x.end(), y) != x.end())

// This funcion expands a file name following simple '*' rules
// Returns a list of names of files, relative to fullPath, according to the pattern
list<wstring>* expand(wstring& pattern, TCHAR *fullPath);

/*
* Simple command line parser.  Will try to read the arguments combo passed by the command line.
* It assumes it will get first some options preceded by a '-' character, either in the form
*	of many single options (-a -b -c) or grouped behind a single '-' character (like -abc).
* The rest of arguments are assumed to be files.
*/
class ArgumentsParser {

private:
	// Parsed arguments
	list<string> options;

	// Parsed files
	list<string> args;

	// Possible options
	set<string> acceptableOptions;
public:
	ArgumentsParser(int theArgc, char* theArgv[], list<string> options);
	// Simple method that reports by the command line the received arguments
	void listArguments();

	// This method returns the list of options parsed
	list<string>& getOptions();

	// This method returns the list of arguments parsed after the options
	list<string>& getArgs();
};