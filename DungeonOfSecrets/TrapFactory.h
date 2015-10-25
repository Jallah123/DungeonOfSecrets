#pragma once
#include "Trap.h"
#include <vector>
#include <string>

using namespace std;

class TrapFactory
{
public:
	static TrapFactory* GetInstance();
	Trap GetRandomTrap();
private:
	void GenerateTraps();
	vector<Trap> Traps;
	TrapFactory();
	~TrapFactory();
	static TrapFactory* instance;
};

