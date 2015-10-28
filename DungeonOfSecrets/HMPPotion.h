#pragma once
#include "Item.h"

class HMPPotion :
	public Item
{
public:
	HMPPotion(string _Name, int _Value) : Item(_Name, _Value) {  };
	~HMPPotion();
	void DoAction() { };
};

