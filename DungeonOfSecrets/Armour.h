#pragma once
#include "Item.h"

class Armour :
	public Item
{
public:
	Armour() { };
	Armour(string _Name, int _Defence) : Item(_Name, _Defence) { };
	int GetDefence() { return Value; };
	~Armour();
private:
	void DoAction() { };
};