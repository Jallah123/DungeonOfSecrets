#pragma once
#include "Item.h"
class Armour :
	public Item
{
public:
	Armour();
	~Armour();
private:
	int Defence;
	void DoAction() {};
};