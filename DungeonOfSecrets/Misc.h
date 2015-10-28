#pragma once
#include "Item.h"
class Misc :
	public Item
{
public:
	Misc(string _Name, int _Value) : Item(_Name, _Value) {};
	~Misc();
	void DoAction() {};
};

