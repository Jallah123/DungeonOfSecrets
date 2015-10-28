#pragma once
#include "Item.h"
class MPPotion :
	public Item
{
public:
	MPPotion(string _Name, int _Value) : Item(_Name, _Value) { };
	~MPPotion();
	void DoAction() {};
};

