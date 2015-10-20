#include "Layer.h"
#include "Utility.h"

Layer::Layer(Difficulty difficulty)
{
	for (int i = 0;i < 5;i++) {
		vector<Room> rooms;
		for (int ii = 0;ii < 5;ii++) {
			rooms.push_back(Room{ difficulty });
		}
		Rooms.push_back(rooms);
	}
	LadderUpRoom = &Rooms.at(Utility::GetInstance()->RandomNumber(0,4)).at(Utility::GetInstance()->RandomNumber(0, 4));
	LadderDownRoom = &Rooms.at(Utility::GetInstance()->RandomNumber(0, 4)).at(Utility::GetInstance()->RandomNumber(0, 4));
}

Layer::Layer() 
{

}

Layer::~Layer()
{
}
