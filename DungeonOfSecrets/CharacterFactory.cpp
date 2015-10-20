#include "CharacterFactory.h"
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Parser.h"

CharacterFactory::CharacterFactory()
{
}


CharacterFactory::~CharacterFactory()
{
}

void CharacterFactory::GenerateCharacters()
{
	vector<vector<string>> characters = Parser::Parse("Characters.txt");
	for (auto &elements : characters) {
		Character c{ elements[0], stoi(elements[1]), stoi(elements[2]), stoi(elements[3]) , stoi(elements[4]) , stoi(elements[5]) , stoi(elements[6]) };
		Characters.push_back(c);
	}
}