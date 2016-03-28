#pragma once

#include <list>
#include <set>

using namespace std;

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