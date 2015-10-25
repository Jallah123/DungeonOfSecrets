#include "Dungeon.h"
#include "CharacterFactory.h"
#include "Utility.h"
#include <iostream>

Dungeon::Dungeon(string name)
{
	unique_ptr<Layer>firstLayer (new Layer{ Enums::Easy });
	// firstLayer.get()->SetLadderDownRoom(nullptr);
	CurrentLayer = firstLayer.get();
	Layers.push_back(move(firstLayer));
	Wizard = Character{name};
	InitializeCommands();
	InitializeDirections();
	CurrentLayer->GetRoom(Wizard.GetX(), Wizard.GetY())->Enter(Wizard);
	Run();

	//Layers.push_back(Layer{ Medium });
	//Layers.push_back(Layer{ Hard });
	//Layers.push_back(Layer{ Boss });
}

void Dungeon::Run() 
{
	system("cls");
	while (running)
	{
		CurrentLayer->Print();
		
		GetCurrentRoom()->PrintEnemies();
		ShowInfo();
		
		char command[100];
		cin.getline(command, sizeof(command));
		system("cls");
		HandleInput(command);
		EnemiesAttack();
	}
}

void Dungeon::ShowInfo() {
	cout << "Hello " << Wizard.GetName() << "," << endl;
	cout << "You currently have [" << Wizard.GetCurrentHP() << "/" << Wizard.GetHP() << "] HP" << endl;
	cout << "You currently have " << Wizard.GetMP() << " MP" << endl;
	cout << "Please enter what you would like to do." << endl << "- >";
}

void Dungeon::HandleInput(string input)
{
	string command = input.substr(0, input.find(' '));
	string value = "";
	size_t found = input.find(" ");
	if(found != string::npos)
		value = input.substr(input.find(' ') + 1, input.length() - 1);
	if (CommandsMap.find(command) == CommandsMap.end()) {
		cout << "Not a valid command, type 'help' for al available commands." << endl;
		return;
	}
	switch (CommandsMap.at(command))
	{
	case go:
		Go(value);
		break;
	case attack:
		AttackEnemy(value);
		break;
	case help:
		ShowHelp();
		break;
	case rest:
		Rest();
		break;
	case info:
		ShowAllInfo();
		break;
	default:
		break;
	}
}

void Dungeon::ShowAllInfo() 
{
	cout << "Level: " << Wizard.GetLevel() << endl;
	cout << "Perception: " << Wizard.GetPerception() << "\t";
	cout << "BaseAttack: " << Wizard.GetBaseAttack() << "\t";
	cout << "BaseDefence: " << Wizard.GetBaseDefence() << endl;
	if (Wizard.GetWeapon().GetName() != "")
	{
		cout << "Weapon: " << Wizard.GetWeapon().GetName() << " " << Wizard.GetWeapon().GetDescription() << ". Damage: " << Wizard.GetWeapon().GetDamage() << endl;
		cout << "Weapon: " << Wizard.GetArmour().GetName() << " " << Wizard.GetArmour().GetDescription() << ". Damage: " << Wizard.GetArmour().GetDefence() << endl;
	}
}

void Dungeon::Rest()
{
	if (Wizard.GetCurrentHP() == Wizard.GetHP()) 
	{
		cout << "You already have full health." << endl;
		return;
	}
	
	Wizard.Heal(Wizard.GetLevel() * 10);
	Room* CurrentRoom = GetCurrentRoom();
	if (Utility::GetInstance()->RandomNumber(0, 9) == 0) 
	{
		CurrentRoom->AddEnemy(CharacterFactory::GetInstance()->GetCharacterByDifficulty(CurrentRoom->GetDifficulty()));
	}
}

void Dungeon::ShowHelp() 
{
	cout << "You can type any if these commands:" << endl;
	for each (auto command in CommandsMap)
	{
		cout << command.first << ", ";
	}
	cout << endl;
}

void Dungeon::AttackEnemy(string index)
{
	if (index == "")
		cout << "Correct usage : attack <number>" << endl;
	int i;
	try {
		i = stoi(index);
	}
	catch (exception e) {
		cout << "Not a valid number" << endl;
		return;
	}
	vector<Character>* enemies = GetCurrentRoom()->GetEnemies();
	if (!enemies->empty() && i <= enemies->size() && i >= 0) {
		if (Wizard.Attack(enemies->at(i))) {
			cout << "You killed " << enemies->at(i).GetName() << endl;
			Wizard.AddXP(enemies->at(i).GetLevel());
			GetCurrentRoom()->GetEnemies()->erase(enemies->begin() + i);
		}
	}
	else {
		cout << "No such enemy" << endl;
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
		cout << "Error using command Go usage: go <direction>" << endl;
		return;
	}
	Room* r = GetCurrentRoom();
	auto dir = DirectionsMap.find(Direction);
	if (dir == DirectionsMap.end()) {
		cout << "No such direction exists" << endl;
		return;
	}
	if (r->GetRoomByDirection(dir->second) != nullptr)
	{
		Wizard.Move(r->GetRoomByDirection(dir->second)->GetX(), r->GetRoomByDirection(dir->second)->GetY());
		r->GetRoomByDirection(dir->second)->Enter(Wizard);
	}
	else {
		cout << "No room there" << endl;
	}
}

void Dungeon::EnemiesAttack() {
	vector<Character>* enemies = GetCurrentRoom()->GetEnemies();
	for (int i = 0; i < enemies->size(); i++)
	{
		enemies->at(i).Attack(Wizard);
	}
}

Dungeon::~Dungeon()
{
}
