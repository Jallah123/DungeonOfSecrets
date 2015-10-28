#pragma once
#include "Item.h"
#include <vector>

using namespace std;

class ItemFactory
{
public:
	static ItemFactory* GetInstance();
	Item* GetRandomItem();
	int GetIndexFromItem(Item* item);
	Item* GetItemFromIndex(int index);
private:
	ItemFactory();
	~ItemFactory();
	void GenerateItems();
	static ItemFactory* instance;
	vector<Item*> Items;
};