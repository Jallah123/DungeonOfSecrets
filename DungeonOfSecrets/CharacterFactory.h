#pragma once
#include <string>
#include "Character.h"
#include "DifficultyEnum.h"

using namespace std;

class CharacterFactory
{
public:
	static CharacterFactory* GetInstance();
	void GenerateCharacters();
	vector<Character> Characters{};
	Character GetCharacterByDifficulty(Enums::Difficulty Difficulty);
private:
	CharacterFactory();
	~CharacterFactory();
	static CharacterFactory* instance;
};

