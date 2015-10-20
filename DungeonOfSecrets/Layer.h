#pragma once
#include <vector>
#include "Room.h"
#include "DifficultyEnum.h"
#include <memory>
class Layer
{
public:
	Layer();
	Layer(Difficulty difficulty);
	void SetLadderUpRoom(Room* room) { LadderUpRoom = room; };
	~Layer();
private:
	vector<vector<Room>> Rooms;
	Room* LadderUpRoom{ nullptr };
	Room* LadderDownRoom{ nullptr };
};

