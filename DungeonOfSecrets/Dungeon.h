#pragma once
#include <vector>
#include <string>
#include "Layer.h"

class Dungeon
{
public:
	Dungeon(string name);
	~Dungeon();
	vector<unique_ptr<Layer>> Layers;
private:
	bool running = true;
	void Run();
	void HandleInput(string input);
	void Go(string direction);
	Character Wizard;
};

