#include "Dungeon.h"
#include "CharacterFactory.h"
#include "Utility.h"
#include <deque>
#include <vector>
#include <iostream>
#include <limits>

Dungeon::Dungeon(string name)
{
	unique_ptr<Layer>firstLayer(new Layer{ Enums::Easy });
	// firstLayer.get()->SetLadderDownRoom(nullptr);
	CurrentLayer = firstLayer.get();
	Layers.push_back(move(firstLayer));
	Wizard = Character{ name };
	InitializeCommands();
	InitializeDirections();
	InitializeStrings();
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
	if (found != string::npos)
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
	case talisman:
		UseTalisman();
		break;
	case showmap:
		RevealMap();
		break;
	case compass:
		UseCompass();
		break;
	case openmap:
		OpenMap();
		break;
	case spawnsuperboss:
		SpawnSuperBoss(value);
		break;
	default:
		break;
	}
}

void Dungeon::RevealMap()
{
	for each (auto& roomrow in CurrentLayer->GetRooms())
	{
		for each (auto& room in roomrow)
		{
			room.get()->SetVisited();
		}
	}
}

void Dungeon::OpenMap()
{
	for each (auto& roomrow in CurrentLayer->GetRooms())
	{
		for each (auto& room in roomrow)
		{
			vector<vector<unique_ptr<Room>>>& rooms = CurrentLayer->GetRooms();

			if ((room.get()->GetY() - 1) >= 0) {
				room.get()->AddDirection(Directions::North, rooms.at(room.get()->GetY() - 1).at(room.get()->GetX()).get());
			}
			if (room.get()->GetX() + 1 < rooms.at(room.get()->GetY()).size()) {
				room.get()->AddDirection(Directions::East, rooms.at(room.get()->GetY()).at(room.get()->GetX() + 1).get());
			}
			if (room.get()->GetY() + 1 < rooms.size()) {
				room.get()->AddDirection(Directions::South, rooms.at(room.get()->GetY() + 1).at(room.get()->GetX()).get());
			}
			if (room.get()->GetX() - 1 >= 0) {
				room.get()->AddDirection(Directions::West, rooms.at(room.get()->GetY()).at(room.get()->GetX() - 1).get());
			}
		}
	}
}

void Dungeon::SpawnSuperBoss(string value)
{
	size_t t = value.find(":");
	int x;
	int y;
	try {
		x = stoi(value.substr(0, t ));
		y = stoi(value.substr(t + 1, value.length() - 1));
	}
	catch (exception e) {

	}
	CurrentLayer->GetRoom(x-1, y-1)->AddEnemy(Character{ "Super Boss", 999999, 999999, 999999 , 999999 , 999999 ,999999 });
}

void Dungeon::UseCompass() {
	Dijkstra();
	Room* target = CurrentLayer->GetLadderRoom();
	vector<Room*> path;
	for (Room* room = target; room != nullptr; room = room->GetPreviousRoom()) {
		path.push_back(room);
	}
	reverse(path.begin(), path.end());

	// Print path
	int index = 0;
	while (index < path.size() - 1)
	{
		cout << StringMap.at(path.at(index)->GetDirectionByRoom(path.at(index + 1))) << " ";
		index++;
	}
	cout << endl;
}

void Dungeon::Dijkstra() {
	vector<vector<unique_ptr<Room>>>& rooms = CurrentLayer->GetRooms();
	for each (auto& roomrow in rooms)
	{
		for each (auto& room in roomrow)
		{
			room.get()->SetDistance(numeric_limits<int>::max());
			room.get()->SetPreviousRoom(nullptr);
		}
	}
	GetCurrentRoom()->SetDistance(0);
	deque<Room*> queue;
	queue.push_back(GetCurrentRoom());

	while (!queue.empty()) {
		Room* room = queue.front();
		queue.pop_front();
		for each (auto& AdjecentRoom in room->GetAdjecentRooms())
		{

			int weight = AdjecentRoom.second->GetWeigth();
			int distance = room->GetDistance() + weight;

			if (distance < AdjecentRoom.second->GetDistance()) {
				AdjecentRoom.second->SetDistance(distance);
				AdjecentRoom.second->SetPreviousRoom(room);
				queue.push_back(AdjecentRoom.second);
			}
		}
	}
}

void Dungeon::UseTalisman()
{
	struct Node {
		Room* Self;
		Room* Parent;

		Node() {};

		Node(Room* _Self, Room* _Parent)
		{
			Self = _Self;
			Parent = _Parent;
		}
	};

	Room* CurrentRoom = GetCurrentRoom();
	if (CurrentRoom == CurrentLayer->GetLadderRoom()) {
		cout << "You are already in the ladderroom." << endl;
		return;
	}
	deque<Room*> queue;
	vector<Room*> visited;
	vector<Node> list;
	queue.push_back(CurrentRoom);

	while (!queue.empty())
	{
		CurrentRoom = queue.back();
		queue.pop_back();
		visited.push_back(CurrentRoom);

		if (CurrentRoom == CurrentLayer->GetLadderRoom())
		{
			Node n = list.back();
			int index = 1;
			while (n.Parent != GetCurrentRoom())
			{
				for each (Node node in list)
				{
					if (node.Self == n.Parent) {
						n = node;
					}
				}
				cout << n.Self->GetX() + 1 << ":" << n.Self->GetY() + 1 << endl;
				index++;
			}
			cout << "Total " << index << " steps till the ladder room." << endl;
		}

		map<Directions, Room*> AdjecentRooms = CurrentRoom->GetAdjecentRooms();
		for each (pair<Directions, Room*> room in AdjecentRooms)
		{
			if (find(visited.begin(), visited.end(), room.second) == visited.end() && find(queue.begin(), queue.end(), room.second) == queue.end())
			{
				list.push_back(Node{ room.second, CurrentRoom });
				queue.push_back(room.second);
			}
		}
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
		cout << "Weapon: " << Wizard.GetWeapon().GetName() << ". Damage: " << Wizard.GetWeapon().GetDamage() << endl;
		cout << "Weapon: " << Wizard.GetArmour().GetName() << ". Damage: " << Wizard.GetArmour().GetDefence() << endl;
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
