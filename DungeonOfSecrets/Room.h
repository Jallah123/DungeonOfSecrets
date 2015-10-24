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
	Room(Difficulty difficulty, int _x, int _y);
	bool IsVisited() { return visited; };
	bool IsDestroyed() { return destroyed; };
	void AddDirection(Directions dir, Room* room) { AdjecentRooms[dir] = room; };
	bool HasEastRoom() { return AdjecentRooms.find(Directions::East) != AdjecentRooms.end(); };
	bool HasSouthRoom() { return AdjecentRooms.find(Directions::South) != AdjecentRooms.end(); };
	int GetX() { return x; }
	int GetY() { return y; }
	~Room();
private:
	string Description;
	int x;
	int y;
	bool visited = false;
	bool destroyed = false;
	vector<Trap> Traps;
	vector<Item> Items;
	vector<Character> Enemies;
	map<Directions, Room*> AdjecentRooms;
};

