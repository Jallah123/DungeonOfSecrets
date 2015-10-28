#pragma once
#include "Item.h"
class HPPotion :
	public Item
{
public:
	HPPotion(string _Name, int _Value) : Item(_Name, _Value) { };
	~HPPotion();
	void DoAction() {};
};

