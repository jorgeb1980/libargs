#include "pch.h"
#include "libargs.h"

#include <string>
#include <list>
#include <set>
#include <iostream>

using namespace std;

// Simple macro to tell if some option is written twice
#define CONTAINS(x, y) (std::find(x.begin(), x.end(), y) != x.end())


// Constructor: parses the command line
ArgumentsParser::ArgumentsParser(int argc, char* theArgv[], list<string> theOptions) {
	for (list<string>::iterator it = theOptions.begin(); it != theOptions.end();) {
		this->acceptableOptions.insert(*it);
	}
	// First, parsing options
	bool parsingOptions = true;
	for (int i = 1; i < argc; i++) {
		string s(theArgv[i]);

		if (s.compare("--help") == 0) {
			if (!CONTAINS(options, s)) {
				options.push_back(s);
			}
		}
		else {
			if (parsingOptions && s[0] == '-') {
				string tmp = s.substr(1, string::npos);
				for (size_t i = 0; i < tmp.length(); i++) {
					string tmp = string(&tmp[i], 1);
					if (!CONTAINS(options, tmp)) {
						options.push_back(tmp);
					}
				}
			}
			if (parsingOptions && s[0] != '-') {
				parsingOptions = false;
			}
			if (!parsingOptions && s[0] == '-') {
				throw s;
			}
			if (!parsingOptions && s[0] != '-') {
				// Argument
				args.push_back(s);
			}
		}
	}
}

// Prints the arguments in the console
void ArgumentsParser::listArguments() {
	cout << "\Options:\n";
	for (list<string>::iterator it = this->options.begin(); it != this->options.end(); it++) {
		string arg = *it;
		cout << (*it).c_str() << "\n";
	}
	cout << "\Arguments:\n";
	for (list<string>::iterator itF = args.begin(); itF != args.end(); itF++) {
		cout << *itF << "\n";
	}
}

// This method returns the list of options parsed
list<string>& ArgumentsParser::getOptions() {
	return options;
}

// This method returns the list of arguments parsed after the options
list<string>& ArgumentsParser::getArgs() {
	return args;
}
