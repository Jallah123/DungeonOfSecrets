#pragma once
#include <string>

using namespace std;

class CharacterFactory
{
public:
	CharacterFactory();
	~CharacterFactory();
	static void GenerateCharacters(string textfile);
};

