#include "Room.h"
#include "RoomFactory.h"

Room::Room(Difficulty Difficulty)
{
	Description = RoomFactory::GetInstance()->GetDescription();
}


Room::~Room()
{
}
