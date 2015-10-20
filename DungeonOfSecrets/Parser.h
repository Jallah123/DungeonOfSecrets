#pragma once
#include <string>
#include <vector>
using namespace std;

class Parser
{
public:
	Parser();
	~Parser();
	static vector<vector<string>> Parse(string textfile);
	static vector<string> &split(const string &s, char delim, vector<string> &elems);
};

