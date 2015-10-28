#include "Room.h"
#include "RoomFactory.h"

Room::Room(Enums::Difficulty _Difficulty, int _x, int _y)
{
	Description = RoomFactory::GetInstance()->GetDescription();
	x = _x;
	y = _y;
	Difficulty = _Difficulty;
	
}

void Room::PrintEnemies() {
	int i = 0;
	for each (Character enemy in Enemies)
	{
		cout << i++ << ". ";
		enemy.Print();
	}
}

void Room::Enter(Character& Wizard) 
{
	cout << Description << endl;
	visited = true;
	if (Trap.IsActivated())
		return;
	if (Trap.GetPerceptionNeeded() >= 0)
		if (Trap.GetPerceptionNeeded() > Wizard.GetPerception()) {
			Trap.DoAction(Wizard);
		} else {
			Trap.Disarm();
			cout << "You disarmed a " << Trap.GetName() << "." << endl;
		}
}

Room* Room::GetRoomByDirection(Directions dir)
{
	if (AdjecentRooms.find(dir) != AdjecentRooms.end())
		return AdjecentRooms.find(dir)->second;
	return nullptr;
}

int Room::GetWeigth()
{
	int weight = 0;
	if (Trap.GetPerceptionNeeded() >= 0) {
		weight += 2;
	}
	for each (auto enemy in Enemies)
	{
		weight += enemy.GetLevel();
	}
	return weight;
}

Directions Room::GetDirectionByRoom(Room* room) 
{
	for each (pair<Directions, Room*> var in AdjecentRooms)
	{
		if (var.second == room) {
			return var.first;
		}
	}
}

Item* Room::GetItem(int i)
{
	if (i < Items.size() && i >= 0) {
		Item* item = Items.at(i);
		RemoveItem(Items.at(i));
		return item;
	}
	cout << "No such item." << endl;
	return nullptr;
}

void Room::PrintItems()
{
	int i = 0;
	cout << "You look around and see: " << endl;
	for each (auto item in Items) {
		cout << i++ << ". "<< item->GetName() << endl;
	}
	if (i == 0) {
		cout << "Nothing." << endl;
	}
}

Room::~Room()
{
}
