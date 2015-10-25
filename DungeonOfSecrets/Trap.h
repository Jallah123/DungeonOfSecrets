#pragma once
#include <string>
#include "Character.h"

using namespace std;

class Trap
{
public:
	Trap();
	Trap(string _Name,  int _HP, int _MP, int _PerceptionNeeded) { Name = _Name; PerceptionNeeded = _PerceptionNeeded; HP = _HP; MP = _MP; };
	void DoAction(Character& Wizard);
	bool IsActivated() { return activated; };
	string GetName() { return Name; };	
	void Disarm() { activated = true; };
	int GetPerceptionNeeded() { return PerceptionNeeded; };
	~Trap();	
private:
	bool activated = false;
	string Name = "";
	int PerceptionNeeded = -1;
	int HP = 0;
	int MP = 0;
};