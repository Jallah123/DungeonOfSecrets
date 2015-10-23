#pragma once
#include <vector>
#include "Layer.h"

class Dungeon
{
public:
	Dungeon();
	~Dungeon();
	vector<unique_ptr<Layer>> Layers;
};

