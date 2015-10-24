#include "Dungeon.h"
#include <iostream>

Dungeon::Dungeon(string name)
{
	unique_ptr<Layer>firstLayer (new Layer{ Easy });
	// firstLayer.get()->SetLadderDownRoom(nullptr);
	CurrentLayer = firstLayer.get();
	Layers.push_back(move(firstLayer));
	Wizard = Character{name};
	InitializeCommands();
	InitializeDirections();
	CurrentLayer->GetRoom(Wizard.GetX(), Wizard.GetY())->Enter();
	Run();

	//Layers.push_back(Layer{ Medium });
	//Layers.push_back(Layer{ Hard });
	//Layers.push_back(Layer{ Boss });
}

void Dungeon::Run() 
{
	while (running)
	{
		CurrentLayer->Print();
		
		GetCurrentRoom()->PrintEnemies();

		cout << "Hello " << Wizard.GetName() << "," << endl << "Please enter what you would like to do." << endl << "- >";
		char command[100];
		cin.getline(command, sizeof(command));
		system("cls");
		HandleInput(command);
	}
}

void Dungeon::HandleInput(string input)
{
	string command = input.substr(0, input.find(' '));
	string value = "";
	size_t found = input.find(" ");
	if(found != string::npos)
		value = input.substr(input.find(' ') + 1, input.length() - 1);
	switch (CommandsMap[command])
	{
	case go:
		Go(value);
		break;
	default:
		break;
	}
}

Room* Dungeon::GetCurrentRoom() 
{
	return 	CurrentLayer->GetRoom(Wizard.GetX(), Wizard.GetY());
}


void Dungeon::Go(string Direction)
{
	if (Direction == "")
	{
		cout << "Error using command Go usage: go <direction>";
		return;
	}
	Room* r = GetCurrentRoom();
	Directions dir = DirectionsMap[Direction];
	switch (dir)
	{
	case North:
	case South:
	case West:
	case Down:
	case East:
		if (r->GetRoomByDirection(dir) != nullptr)
		{
			Wizard.Move(r->GetRoomByDirection(dir)->GetX(), r->GetRoomByDirection(dir)->GetY());
			r->GetRoomByDirection(dir)->Enter();
		}
		else {
			cout << "No room" << endl;
		}
		break;
	default:
		cout << "No known directions has been chosen.";
		break;
	}

}

Dungeon::~Dungeon()
{
}
