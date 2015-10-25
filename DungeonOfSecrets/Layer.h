#pragma once
#include <vector>
#include "Room.h"
#include "DifficultyEnum.h"
#include "DirectionsEnum.h"
#include <memory>

class Layer
{
public:
	Layer();
	Layer(Enums::Difficulty difficulty);
	void Print();
	Directions GetDirectionToRoom(int currentX, int currentY, int destX, int destY);
	Room* GetRoom(int x, int y) { return Rooms.at(y).at(x).get(); };
	void SetLadderDownRoom(unique_ptr<Room> room) { LadderDownRoom = room.get(); };
	int index = 0;
	~Layer();
private:
	void FillRooms(Enums::Difficulty difficulty);
	vector<Room*> GetAdjecentRooms(int x, int y);
	vector<vector<unique_ptr<Room>>> Rooms;
	void GenerateConnections();
	Room* LadderDownRoom{ nullptr };
	void LinkRooms(Room* room1, Room* room2);
	vector<Room*> GenerateConnections(Room* room, vector<Room*> VisitedRooms);
};

