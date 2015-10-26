#pragma once
#include <string>

using namespace std;

class Item
{
public:
	Item() { Name = ""; };
	Item(string _Name) { Name = _Name; };
	~Item();
	string GetName() { return Name; };
	virtual void DoAction() = 0;
private:
	string Name;
};

