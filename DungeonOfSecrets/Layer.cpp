#include "Layer.h"
#include "Utility.h"
#include <iostream>

Layer::Layer(Difficulty difficulty)
{
	for (int y = 0;y < 5;y++) {
		vector<unique_ptr<Room>> rooms;
		for (int x = 0;x < 5;x++) {
			rooms.push_back(unique_ptr<Room>(new Room{difficulty, x, y}));
		}
		Rooms.push_back(move(rooms));
	}
	LadderDownRoom = Rooms.at(Utility::GetInstance()->RandomNumber(0, 4)).at(Utility::GetInstance()->RandomNumber(0, 4)).get();
	GenerateConnections();
}

void Layer::GenerateConnections() 
{
	vector<Room*> VisitedRooms;
	Utility* util = Utility::GetInstance();
	int x = util->RandomNumber(0, Rooms.size() - 1);
	int y = util->RandomNumber(0, Rooms.at(x).size() - 1);

	Room* CurrentRoom = Rooms.at(x).at(y).get();

	GenerateConnections(CurrentRoom, VisitedRooms);
}

void Layer::GenerateConnections(Room* room, vector<Room*> VisitedRooms) {
	vector<Room*> AdjecentRooms = GetAdjecentRooms(room->GetX(), room->GetY());

	while (!AdjecentRooms.empty()) {
		int IndexChosenNeighbor = Utility::GetInstance()->RandomNumber(0, AdjecentRooms.size() - 1);
		Room* ChosenNeighbor = AdjecentRooms.at(IndexChosenNeighbor);
		if (VisitedRooms.size() == Rooms.size())
			return;
		if (find(VisitedRooms.begin(), VisitedRooms.end(), ChosenNeighbor) == VisitedRooms.end()) {
			LinkRooms(room, ChosenNeighbor);
			VisitedRooms.push_back(room);
			Room* CurrentRoom = ChosenNeighbor;
			GenerateConnections(CurrentRoom, VisitedRooms);
		}
		else {
			auto index = find(AdjecentRooms.begin(), AdjecentRooms.end(), ChosenNeighbor);
			AdjecentRooms.erase(index);
		}
	}
}

void Layer::LinkRooms(Room* room1, Room* room2)
{
	Directions dir = GetDirectionToRoom(room1->GetX(), room1->GetY() , room2->GetX(), room2->GetY());
	room1->AddDirection(dir, room2);
	dir = GetDirectionToRoom(room2->GetX(), room2->GetY(), room1->GetX(), room1->GetY());
	room2->AddDirection(dir, room1);
}

Directions Layer::GetDirectionToRoom(int currentX, int currentY, int destX, int destY) 
{
	if (currentX < destX)
		return Directions::East;
	else if (currentX > destX)
		return Directions::West;
	if (currentY < destY)
		return Directions::South;
	else if (currentY > destY)
		return Directions::North;
}

vector<Room*> Layer::GetAdjecentRooms(int x, int y) 
{
	vector<Room*> AdjecentRooms;
	
	if (x - 1 >= 0) {
		if (Rooms.at(x - 1).at(y) != nullptr) {
			AdjecentRooms.push_back(Rooms.at(x - 1).at(y).get());
		}
	}
	if (x + 1 <= Rooms.size() - 1) {
		if (Rooms.at(x + 1).at(y) != nullptr) {
			AdjecentRooms.push_back(Rooms.at(x + 1).at(y).get());
		}
	}
	if (y - 1 >= 0) {
		if (Rooms.at(x).at(y - 1) != nullptr) {
			AdjecentRooms.push_back(Rooms.at(x).at(y-1).get());
		}
	}
	if (y + 1 <= Rooms.at(x).size() - 1) {
		if (Rooms.at(x).at(y + 1) != nullptr) {
			AdjecentRooms.push_back(Rooms.at(x).at(y + 1).get());
		}
	}
	return AdjecentRooms;
}

void Layer::Print() 
{
	for each (auto& RoomsRow in Rooms)
	{
		string line = "";
		for each (auto& Room in RoomsRow)
		{
			if (Room.get() == LadderDownRoom) {
				cout << "T";
			}
			else if (Room.get()->IsDestroyed()) {
				cout << "~";
			}
			else if (Room.get()->IsVisited()) {
				cout << "N";
			}
			else {
				cout << "O";
			}

			if (Room.get()->HasEastRoom())
				cout << "-";
			else 
				cout << " ";

			if (Room.get()->HasSouthRoom())
				line += "l ";
			else
				line += "  ";
		}
		cout << endl << line << endl;
	}
}

Layer::Layer() 
{

}

Layer::~Layer()
{
	LadderDownRoom = nullptr;
}
