#include <iostream>
#include <string>
#include "Dungeon.h"

int main()
{
	char name[100];
	cout << "Hello wizard, please enter your name : ";
	cin.getline(name, sizeof(name));

	Dungeon d{name};
	system("pause");
}
