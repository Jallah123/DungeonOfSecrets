#pragma once
#include "Item.h"
class Weapon :
	public Item
{
public:
	Weapon() {};
	Weapon(string _Name, int _Damage) : Item(_Name) { Damage = _Damage; };
	~Weapon();
	int GetDamage() { return Damage; };
private:
	int Damage;
	void DoAction() {};
};

