#pragma once
#include <string>

using namespace std;

class Item
{
public:
	Item();
	~Item();
	string GetName() { return Name; };
	string GetDescription() { return Description; };
	virtual void DoAction() = 0;
private:
	string Name;
	string Description;
};

