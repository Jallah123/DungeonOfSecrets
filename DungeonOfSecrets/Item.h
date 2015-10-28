#pragma once
#include <string>

using namespace std;

class Item
{
public:
	Item() { Name = ""; Value = 0; };
	Item(string _Name, int _Value) { Name = _Name; Value = _Value; };
	~Item();
	string GetName() { return Name; };
	int GetValue() { return Value; };
	virtual void DoAction() = 0;
protected:
	string Name;
	int Value;
};

