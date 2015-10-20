#pragma once
#include <string>
#include <vector>
#include <map>
#include "Trap.h"
#include "Item.h"
#include <memory>
#include "Character.h"
#include "DirectionsEnum.h"
#include "DifficultyEnum.h"

using namespace std;

class Room
{
public:
	Room(Difficulty difficulty);
	~Room();
private:
	string Description;
	vector<Trap> Traps;
	vector<Item*> Items;
	vector<Character> Enemies;
	map<Directions, Room*> AdjecentRooms;
};

