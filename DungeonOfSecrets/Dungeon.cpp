#include "Dungeon.h"

Dungeon::Dungeon()
{
	Layer firstLayer{ Easy };
	firstLayer.SetLadderUpRoom(nullptr);
	Layers.push_back(firstLayer);
	//Layers.push_back(Layer{ Medium });
	//Layers.push_back(Layer{ Hard });
	//Layers.push_back(Layer{ Boss });
}


Dungeon::~Dungeon()
{
}
