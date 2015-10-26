#pragma once
#include "Item.h"
class Armour :
	public Item
{
public:
	Armour() { };
	Armour(string _Name, int _Defence) : Item(_Name) { Defence = _Defence; };
	int GetDefence() { return Defence; };
	~Armour();
private:
	int Defence;
	void DoAction() {};
};