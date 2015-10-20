#pragma once
#include <string>
#include <vector>
#include <map>
#include "Trap.h"
#include "Item.h"
#include "Character.h"
using namespace std;

class Room
{
public:
	Room();
	~Room();
private:
	string Description;
	vector<Trap> Traps;
	vector<Item> Items;
	vector<Character> Enemies;
	map<string, Room> AdjecentRooms;
};

