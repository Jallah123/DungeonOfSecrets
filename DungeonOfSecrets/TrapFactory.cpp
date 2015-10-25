#include "TrapFactory.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include "Parser.h"
#include "Utility.h"

TrapFactory::TrapFactory()
{
	GenerateTraps();
}

TrapFactory* TrapFactory::instance{ nullptr }; // definition & init

TrapFactory* TrapFactory::GetInstance() {
	if (instance == nullptr) {
		instance = new TrapFactory;
	}
	return instance;
}

void TrapFactory::GenerateTraps() 
{
	vector<vector<string>> characters = Parser::Parse("Traps.txt");
	for (auto &elements : characters) {
		Trap trap{ elements[0], stoi(elements[1]), stoi(elements[2]), stoi(elements[3]) };
		Traps.push_back(trap);
	}
}

Trap TrapFactory::GetRandomTrap()
{
	return Traps.at(Utility::GetInstance()->RandomNumber(0, Traps.size() - 1));
}




TrapFactory::~TrapFactory()
{
}
