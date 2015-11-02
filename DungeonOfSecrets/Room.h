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
	Room(Enums::Difficulty _Difficulty, int _x, int _y);
	bool IsVisited() { return visited; };
	void AddDirection(Directions dir, Room* room) { AdjecentRooms[dir] = room; AdjecentRoomsEdges[dir] = false; };
	bool HasEastRoom() { return AdjecentRooms.find(Directions::East) != AdjecentRooms.end(); };
	bool HasSouthRoom() { return AdjecentRooms.find(Directions::South) != AdjecentRooms.end(); };
	bool HasWestRoom() { return AdjecentRooms.find(Directions::West) != AdjecentRooms.end(); };
	bool HasNorthRoom() { return AdjecentRooms.find(Directions::North) != AdjecentRooms.end(); };
	void SetVisited() { visited = true; };
	map<Directions, Room*> GetAdjecentRooms() { return AdjecentRooms; };
	map<Directions, bool> GetAdjecentRoomsEdges() { return AdjecentRoomsEdges; };
	void DestroyEdge(Directions dir) { AdjecentRoomsEdges[dir] = true; };
	bool DirectionDestroyed(Directions dir) { return AdjecentRoomsEdges[dir]; };
	void SetTrap(Trap _Trap) { Trap = _Trap; };
	Enums::Difficulty GetDifficulty() { return Difficulty; };
	void AddEnemy(Character Enemy) { Enemies.push_back(Enemy); };
	vector<Character>* GetEnemies() { return &Enemies; };
	void PrintEnemies();
	Room* GetRoomByDirection(Directions dir);
	Directions GetDirectionByRoom(Room* room);
	int GetX() { return x; }
	int GetY() { return y; }
	void Enter(Character& Wizard);
	int GetWeigth();
	int GetDistance() { return Distance; };
	Room* GetPreviousRoom() { return PreviousRoom; };
	void SetPreviousRoom(Room* _PreviousRoom) { PreviousRoom = _PreviousRoom; };
	void SetDistance(int _Distance) { Distance = _Distance; };
	void AddItem(Item* item) { Items.push_back(item); };
	void RemoveItem(Item* item) { auto i = find(Items.begin(), Items.end(), item); Items.erase(i); };
	Item* GetItem(int i);
	void PrintItems();
	~Room();
private:
	int Distance = numeric_limits<int>::max();
	Room* PreviousRoom{ nullptr };
	string Description;
	Enums::Difficulty Difficulty;
	int x;
	int y;
	bool visited = false;
	Trap Trap;
	vector<Item*> Items;
	vector<Character> Enemies;
	map<Directions, Room*> AdjecentRooms;
	map<Directions, bool> AdjecentRoomsEdges;
};

