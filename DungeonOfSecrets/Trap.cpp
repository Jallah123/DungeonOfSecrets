#include "Trap.h"

Trap::Trap()
{
}

void Trap::DoAction(Character& Wizard) 
{
	Wizard.Damage(HP);
	Wizard.DrainMP(MP);
	cout << "You activated a " << Name << " trap " << endl;
	activated = true;
}


Trap::~Trap()
{
}