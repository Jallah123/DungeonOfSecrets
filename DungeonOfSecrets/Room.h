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
#include <iostream>

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
	bool HasWestRoom() { return AdjecentRooms.find(Directions::West) != AdjecentRooms.end(); };
	bool HasNorthRoom() { return AdjecentRooms.find(Directions::North) != AdjecentRooms.end(); };
	void AddEnemy(Character Enemy) { Enemies.push_back(Enemy); };
	vector<Character>* GetEnemies() { return &Enemies; };
	void PrintEnemies() {
		int i = 0;
		for each (Character enemy in Enemies)
		{
			cout << i++ << ". ";
			enemy.Print();
		}
	};
	Room* GetRoomByDirection(Directions dir) { 
		if(AdjecentRooms.find(dir) != AdjecentRooms.end())
			return AdjecentRooms.find(dir)->second; 
		return nullptr;
	};
	int GetX() { return x; }
	int GetY() { return y; }
	void Enter() { cout << Description << endl; visited = true; };
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

