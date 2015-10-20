#pragma once
#include "Item.h"
class Weapon :
	public Item
{
public:
	Weapon();
	~Weapon();
	int GetDamage() { return Damage; };
private:
	int Damage;
	void DoAction() {};
};

