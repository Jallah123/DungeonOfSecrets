#include "CharacterFactory.h"
#include <iostream>
#include <fstream>
#include <string>

CharacterFactory::CharacterFactory()
{
}


CharacterFactory::~CharacterFactory()
{
}

void CharacterFactory::GenerateCharacters(string textfile)
{
	// variabelen waarin de ingelezen waarden terecht komen
	string Name;
	int Level;
	int HP;
	int MP;
	int XP;
	int BaseAttack;
	int BaseDefence;
	int Perception;

	// input file stream, opent textfile voor lezen
	ifstream input_file{ textfile };

	string line;
	// laat even zien wat we hebben gelezen
	while (getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt
		cout << Name << " " << Level << " " << HP << " " << MP << " " << XP << " " << BaseAttack << " " << BaseDefence << " " << Perception << endl;
	}
}