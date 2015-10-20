#pragma once
#include <string>
#include "Character.h"

using namespace std;

class CharacterFactory
{
public:
	CharacterFactory();
	~CharacterFactory();
	void GenerateCharacters();
	vector<Character> Characters {};
};

