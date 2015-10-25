#pragma once
#include "Item.h"
class Armour :
	public Item
{
public:
	Armour() { Defence = 0; };
	int GetDefence() { return Defence; };
	~Armour();
private:
	int Defence;
	void DoAction() {};
};