#pragma once
#include "Item.h"
#include <vector>

using namespace std;

class ItemFactory
{
public:
	static ItemFactory* GetInstance();
	void GenerateItems();
	Item* GetRandomItem();
private:
	ItemFactory();
	~ItemFactory();
	static ItemFactory* instance;
	vector<Item*> Items;
};