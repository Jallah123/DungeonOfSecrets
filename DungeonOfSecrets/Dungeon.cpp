#include "Dungeon.h"
#include "CharacterFactory.h"
#include "Utility.h"
#include <deque>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include "ItemFactory.h"
#include <algorithm>
#include <tuple>

Dungeon::Dungeon(string name)
{
	unique_ptr<Layer>firstLayer(new Layer{ Enums::Easy });
	unique_ptr<Layer>secondLayer(new Layer{ Enums::Medium });
	unique_ptr<Layer>thirdLayer(new Layer{ Enums::Hard });
	unique_ptr<Layer>bossLayer(new Layer{ Enums::Boss });
	// firstLayer.get()->SetLadderDownRoom(nullptr);
	CurrentLayer = firstLayer.get();
	Layers.push_back(move(firstLayer));
	Layers.push_back(move(secondLayer));
	Layers.push_back(move(thirdLayer));
	Layers.push_back(move(bossLayer));
	for (int i = 0; i < Layers.size() - 1; i++) {
		Layers.at(i).get()->GetLadderRoom()->AddDirection(Directions::Down, Layers.at(i + 1)->GetRoom(Utility::GetInstance()->RandomNumber(0, 4), Utility::GetInstance()->RandomNumber(0, 4)));
	}
	Wizard = Character{ name };
	InitializeCommands();
	InitializeDirections();
	InitializeStrings();
	CurrentLayer->GetRoom(Wizard.GetX(), Wizard.GetY())->Enter(Wizard);
	Run();
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
	case look:
		Look();
		break;
	case pickup:
		Pickup(value);
		break;
	case bag:
		Wizard.ShowBag();
		break;
	case use:
		UseItem(value);
		break;
	case save:
		Save();
		break;
	case load:
		Load();
		break;
	case grenade:
		SpanningTree();
		break;
	default:
		break;
	}
}

void Dungeon::Look()
{
	GetCurrentRoom()->PrintItems();
}

void Dungeon::UseItem(string value)
{
	int val;
	try {
		val = stoi(value);
	}
	catch (exception e) {
		cout << "Not a valid number." << endl;
		return;
	}
	Wizard.UseItem(val);
}

void Dungeon::Pickup(string value) {
	int val;
	try {
		val = stoi(value);
	}
	catch (exception e) {
		cout << "Not a valid number." << endl;
		return;
	}
	Item* i = GetCurrentRoom()->GetItem(val);
	if (i != nullptr) {
		Wizard.AddToBag(i);
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
		x = stoi(value.substr(0, t));
		y = stoi(value.substr(t + 1, value.length() - 1));
	}
	catch (exception e) {

	}
	CurrentLayer->GetRoom(x - 1, y - 1)->AddEnemy(Character{ "Super Boss", 999999, 999999, 999999 , 999999 , 999999 ,999999 });
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
void Dungeon::SpanningTree() {
	vector<tuple<Room*, Directions, Room*>> Vertexes;
	vector<tuple<Room*, Directions, Room*>> Tree;
	for each (auto& roomrow in CurrentLayer->GetRooms())
	{
		for each (auto& room in roomrow)
		{
			for each (auto& adjecentRoom in room.get()->GetAdjecentRooms())
			{
				if (adjecentRoom.first == Directions::East || adjecentRoom.first == adjecentRoom.first == Directions::South)
					Vertexes.push_back(make_tuple(room.get(), room.get()->GetDirectionByRoom(adjecentRoom.second), adjecentRoom.second));
			}
		}
	}
	int size = CurrentLayer->GetRooms().size();
	int amountToDestroy = ((size * (size - 1)) * 2) - ((size)* (size)-1);
	//int amountToDestroy = 16;
	while (Tree.size() < amountToDestroy) {
		int lowestWeight = numeric_limits<int>::max();
		tuple<Room*, Directions, Room*> lowestTupel;
		for each (auto& vertex in Vertexes)
		{
			if (get<2>(vertex)->GetWeigth() < lowestWeight && (!Exists(Tree, get<0>(vertex)) || !Exists(Tree, get<2>(vertex)))) {
				lowestWeight = get<2>(vertex)->GetWeigth();
				lowestTupel = vertex;
			}
		}
		Tree.push_back(lowestTupel);
	}
	for each (auto& edges in Tree)
	{
		if (get<1>(edges) == Directions::North) {
			get<2>(edges)->DestroyEdge(Directions::South);
			get<0>(edges)->DestroyEdge(Directions::North);
			continue;
		}
		if (get<1>(edges) == Directions::West) {
			get<2>(edges)->DestroyEdge(Directions::East);
			get<0>(edges)->DestroyEdge(Directions::West);
			continue;
		}
		if (get<1>(edges) == Directions::East) {
			get<2>(edges)->DestroyEdge(Directions::West);
			get<0>(edges)->DestroyEdge(Directions::East);
			continue;
		}
		if (get<1>(edges) == Directions::South) {
			get<2>(edges)->DestroyEdge(Directions::North);
			get<0>(edges)->DestroyEdge(Directions::South);
			continue;
		}
		//cout << get<0>(edges)->GetX()+1 << ":" << get<0>(edges)->GetY()+1 << " " << StringMap.at(get<1>(edges)) << " " << get<2>(edges)->GetX()+1 << ":" << get<2>(edges)->GetY()+1 << endl;
	}
}
/*
void Dungeon::SpanningTree() {
	vector<tuple<Room*, Directions, Room*>> Edges;
	Room* currentRoom = GetCurrentRoom();
	Directions currentRoomMinimumWeightDirection;
	int currentRoomMinimumWeight = numeric_limits<int>::max();
	for (auto room : currentRoom->GetAdjecentRooms()) {
		if (room.second->GetWeigth() < currentRoomMinimumWeight) {
			currentRoomMinimumWeight = room.second->GetWeigth();
			currentRoomMinimumWeightDirection = room.first;
		}
	}
	Edges.push_back(make_tuple(currentRoom, currentRoomMinimumWeightDirection, currentRoom->GetRoomByDirection(currentRoomMinimumWeightDirection)));
	int size = CurrentLayer->GetRooms().size();

	while (Edges.size() < ((size * (size - 1)) * 2) - ((size)* (size)-1)) {
		Directions minimumWeightDirection;
		int minimumWeight = numeric_limits<int>::max();
		currentRoom = nullptr;
		for (auto& room : Edges) {
			for (auto& adjecentRoom : get<0>(room)->GetAdjecentRooms()) {
				bool exists = Exists(Edges, adjecentRoom.second);
				if (adjecentRoom.second->GetWeigth() < minimumWeight && !exists) {
					minimumWeight = adjecentRoom.second->GetWeigth();
					minimumWeightDirection = adjecentRoom.second->GetDirectionByRoom(get<0>(room));
					currentRoom = adjecentRoom.second;
				}
			}
		}
		if (currentRoom == nullptr) { cout << "NULLPOINTER" << endl; }
		else {
			Edges.push_back(make_tuple(currentRoom, minimumWeightDirection, currentRoom->GetRoomByDirection(minimumWeightDirection)));
		}
	}

	for each (auto& edges in Edges)
	{
		if (get<1>(edges) == Directions::North) {
			get<2>(edges)->DestroyEdge(Directions::South);
			get<0>(edges)->DestroyEdge(Directions::North);
		}
		if (get<1>(edges) == Directions::West) {
			get<2>(edges)->DestroyEdge(Directions::East);
			get<0>(edges)->DestroyEdge(Directions::West);
		}
		if (get<1>(edges) == Directions::East) {
			get<0>(edges)->DestroyEdge(Directions::West);
			get<0>(edges)->DestroyEdge(Directions::East);
		}
		if (get<1>(edges) == Directions::South) {
			get<0>(edges)->DestroyEdge(Directions::North);
			get<0>(edges)->DestroyEdge(Directions::South);
		}
		//cout << get<0>(edges)->GetX()+1 << ":" << get<0>(edges)->GetY()+1 << " " << StringMap.at(get<1>(edges)) << " " << get<2>(edges)->GetX()+1 << ":" << get<2>(edges)->GetY()+1 << endl;
	}

}
*/

bool Dungeon::Exists(vector<tuple<Room*, Directions, Room*>>& Edges, Room* Room) {
	for (auto& pair : Edges) {
		if (get<0>(pair) == Room || get<2>(pair) == Room) {
			return true;
		}
	}
	return false;
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
	ResetDistances();
	Room* CurrentRoom = GetCurrentRoom();
	if (CurrentRoom == CurrentLayer->GetLadderRoom()) {
		cout << "You are already in the ladderroom." << endl;
		return;
	}
	deque<Room*> queue;
	CurrentRoom->SetDistance(0);
	queue.push_back(CurrentRoom);

	while (!queue.empty())
	{
		CurrentRoom = queue.back();
		queue.pop_back();

		map<Directions, Room*> AdjecentRooms = CurrentRoom->GetAdjecentRooms();
		for each (pair<Directions, Room*> room in AdjecentRooms)
		{
			if (room.second->GetDistance() == numeric_limits<int>::max())
			{
				room.second->SetDistance(CurrentRoom->GetDistance() + 1);
				queue.push_back(room.second);
				if (room.second == CurrentLayer->GetLadderRoom())
				{
					cout << "Total " << room.second->GetDistance() << " steps till the ladder room." << endl;
					return;
				}
			}
		}
	}
}

void Dungeon::ResetDistances()
{
	for each (auto& roomrow in CurrentLayer->GetRooms())
	{
		for each (auto& room in roomrow)
		{
			room.get()->SetDistance(numeric_limits<int>::max());
		}
	}
}

void Dungeon::ShowAllInfo()
{
	cout << "Level: " << Wizard.GetLevel() << endl;
	cout << "Perception: " << Wizard.GetPerception() << "\t";
	cout << "BaseAttack: " << Wizard.GetBaseAttack() << "\t";
	cout << "BaseDefence: " << Wizard.GetBaseDefence() << endl;
	if (Wizard.GetWeapon() != nullptr)
	{
		cout << "Weapon: " << Wizard.GetWeapon()->GetName() << ". Damage: " << Wizard.GetWeapon()->GetDamage() << endl;
	}
	if (Wizard.GetArmour() != nullptr) {
		cout << "Armour: " << Wizard.GetArmour()->GetName() << ". Defence: " << Wizard.GetArmour()->GetDefence() << endl;
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
		if (!r->DirectionDestroyed(dir->second)) {
			Wizard.Move(r->GetRoomByDirection(dir->second)->GetX(), r->GetRoomByDirection(dir->second)->GetY());
			r->GetRoomByDirection(dir->second)->Enter(Wizard);
			if (dir->second == Directions::Down) {
				int index;
				for (int i = 0; i < Layers.size(); i++) {
					if (Layers.at(i).get() == CurrentLayer) {
						index = i + 1;
					}
				}
				if (index > 0 && index < Layers.size()) {
					CurrentLayer = Layers.at(index).get();
				}
			}
		}
		else {
			cout << "This passage has been destroyed." << endl;
		}
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

void Dungeon::Save()
{
	ofstream output_file{ Wizard.GetName() + ".wizard" };
	output_file << Wizard.GetSaveString();
}

void Dungeon::Load()
{
	Wizard.Load();
}

Dungeon::~Dungeon()
{
}
