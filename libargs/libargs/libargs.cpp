#include "pch.h"
#include "libargs.h"

#include <string>
#include <list>
#include <set>
#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <memory>

using namespace std;

// This funcion expands a file name following simple '*' rules
// Returns a list of names of files, relative to fullPath, according to the pattern
list<wstring>* expand(wstring& pattern, TCHAR *fullPath) {
	list<wstring>* ret = new list<wstring>;
	
	// Own file data
	WIN32_FIND_DATA searchData;
	// Clean the result
	memset(&searchData, 0, sizeof(WIN32_FIND_DATA));

	wstring wpath(fullPath);
	wpath.append(TEXT("\\"));
	wpath.append(pattern);

	HANDLE handle = FindFirstFileEx(
		wpath.c_str(), 
		FindExInfoStandard, 
		&searchData, 
		FindExSearchNameMatch, 
		NULL, 
		0);

	while (handle != INVALID_HANDLE_VALUE) {
		if (_tcscmp(searchData.cFileName, TEXT(".")) != 0 && _tcscmp(searchData.cFileName, TEXT("..")) != 0) {
			wstring ws(fullPath);
			ws.append(TEXT("\\"));
			ws.append(searchData.cFileName);
			ret->push_back(ws);
		}
		int next = FindNextFile(handle, &searchData);
		if (next == FALSE)
			break;
	}


	//Close the handle after use or memory/resource leak
	FindClose(handle);

	return ret;
}

// Constructor: parses the command line
ArgumentsParser::ArgumentsParser(int argc, char* theArgv[], list<string> theOptions) {
	for (list<string>::iterator it = theOptions.begin(); it != theOptions.end(); it++) {
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
					string thestr = string(&tmp[i], 1);
					if (!CONTAINS(options, thestr)) {
						if (CONTAINS(acceptableOptions, thestr)) {
							options.push_back(thestr);
						}
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
	cout << "Options:\n";
	for (list<string>::iterator it = this->options.begin(); it != this->options.end(); it++) {
		string arg = *it;
		cout << (*it).c_str() << "\n";
	}
	cout << "Arguments:\n";
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
