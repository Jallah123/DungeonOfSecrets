#pragma once
#include "Item.h"
class Armour :
	public Item
{
public:
	Armour() { Defence = 0; };
	~Armour();
private:
	int Defence;
	void DoAction() {};
};