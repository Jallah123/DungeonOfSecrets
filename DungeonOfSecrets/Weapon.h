#pragma once
#include "Item.h"
class Weapon :
	public Item
{
public:
	Weapon() { Damage = 0; };
	~Weapon();
	int GetDamage() { return Damage; };
private:
	int Damage;
	void DoAction() {};
};

