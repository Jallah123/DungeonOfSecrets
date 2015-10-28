#pragma once
#include "Item.h"
class Weapon :
	public Item
{
public:
	Weapon() {};
	Weapon(string _Name, int _Damage) : Item(_Name, _Damage) { };
	~Weapon();
	int GetDamage() { return Value; };
private:
	void DoAction() {};
};

