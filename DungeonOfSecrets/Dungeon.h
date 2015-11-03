#pragma once
#include <vector>
#include <string>
#include "Layer.h"
#include "CommandEnum.h"

class Dungeon
{
public:
	Dungeon(string name);
	~Dungeon();
	vector<unique_ptr<Layer>> Layers;
private:
	Layer* CurrentLayer{ nullptr };
	bool running = true;
	void Run();
	void Rest();
	void ShowAllInfo();
	void UseTalisman();
	void RevealMap();
	void HandleInput(string input);
	void Go(string direction);
	Character Wizard;
	Room* GetCurrentRoom();
	void AttackEnemy(string index);
	void ShowHelp();
	void EnemiesAttack();
	void ShowInfo();
	void UseCompass();
	void Dijkstra();
	void SpanningTree();
	void OpenMap();
	void SpawnSuperBoss(string value);
	void Look();
	void Pickup(string value);
	void UseItem(string value);
	void Save();
	void Load();
	bool Exists(vector<tuple<Room*, Directions, Room*>>& Edges, Room* Room);
	bool Exists(vector<tuple<Room*, Directions>>& Edges, Room* Room);
	void Dungeon::Prim();
	bool Dungeon::ExistsInTree(vector<tuple<Room*, Directions, Room*>> Tree, Room* Room);
	void Dungeon::DestroyEdges(vector<tuple<Room*, Directions, Room*>> Tree);
	void Dungeon::DestroyMap();
	bool Dungeon::ExistsInVisited(vector<Room*> Vertexes, Room* Room);
	void Dungeon::CheckDuplicated(vector<Room*> Vertexes);
};