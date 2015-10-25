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

Room::~Room()
{
}
