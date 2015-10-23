#include "Dungeon.h"

Dungeon::Dungeon()
{
	unique_ptr<Layer>firstLayer (new Layer{ Easy });
	firstLayer.get()->SetLadderDownRoom(nullptr);
	Layers.push_back(move(firstLayer));
	Layers.at(0)->Print();
	//Layers.push_back(Layer{ Medium });
	//Layers.push_back(Layer{ Hard });
	//Layers.push_back(Layer{ Boss });
}


Dungeon::~Dungeon()
{
}
