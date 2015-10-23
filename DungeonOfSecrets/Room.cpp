#include "Room.h"
#include "RoomFactory.h"

Room::Room(Difficulty Difficulty, int _x, int _y)
{
	Description = RoomFactory::GetInstance()->GetDescription();
	x = _x;
	y = _y;
}


Room::~Room()
{
}
