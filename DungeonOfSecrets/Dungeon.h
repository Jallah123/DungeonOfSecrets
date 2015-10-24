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
	void HandleInput(string input);
	void Go(string direction);
	Character Wizard;
	Room* GetCurrentRoom();
	void AttackEnemies();
};

