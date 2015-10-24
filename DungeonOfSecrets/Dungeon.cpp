#include "Dungeon.h"
#include "CommandEnum.h"
#include <iostream>


Dungeon::Dungeon(string name)
{
	unique_ptr<Layer>firstLayer (new Layer{ Easy });
	firstLayer.get()->SetLadderDownRoom(nullptr);
	Layers.push_back(move(firstLayer));
	Layers.at(0)->Print();
	Wizard = Character{name};
	initialize();
	Run();

	//Layers.push_back(Layer{ Medium });
	//Layers.push_back(Layer{ Hard });
	//Layers.push_back(Layer{ Boss });
}

void Dungeon::Run() 
{
	while (running)
	{
		system("cls");
		cout << "Hello " << Wizard.GetName() << endl << "Please enter what you would like to do." << endl << "- >";

		char command[100];
		cin.getline(command, sizeof(command));
		HandleInput(command);
	}
}

void Dungeon::HandleInput(string input)
{
	string command = input.substr(0, input.find(' '));
	string value = "";
	size_t found = input.find(" ");
	if(found != string::npos)
		value = input.substr(input.find(' '), input.length() - 1);
	switch (s_mapStringValues[command])
	{
	case go:
		Go(value);
		break;
	default:
		break;
	}
}


void Dungeon::Go(string Direction)
{
	if (Direction == "")
	{
		cout << "Error using command Go usage: <go> <direction>";
		return;
	}
	cout << Direction;

}

Dungeon::~Dungeon()
{
}
