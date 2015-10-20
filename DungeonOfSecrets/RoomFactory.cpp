#include "RoomFactory.h"
#include "Parser.h"
#include "Utility.h"

RoomFactory* RoomFactory::instance{ nullptr }; // definition & init

RoomFactory* RoomFactory::GetInstance() {
	if (instance == nullptr) {
		instance = new RoomFactory;
	}
	return instance;
}

RoomFactory::RoomFactory()
{
	Descriptions = Parser::Parse("Rooms.txt");
}

string RoomFactory::GetDescription()
{
	string des;
	Utility* util = Utility::GetInstance();
	des += "This room is " + Descriptions.at(0).at(util->RandomNumber(0, Descriptions.at(0).size() - 1));
	des += "and " + Descriptions.at(1).at(util->RandomNumber(0, Descriptions.at(1).size() - 1)) + ". ";
	des += "You see " + Descriptions.at(2).at(util->RandomNumber(0, Descriptions.at(2).size() - 1)) + ". ";
	des += "The room is filled with " + Descriptions.at(3).at(util->RandomNumber(0, Descriptions.at(3).size() - 1));
	des += "and luminated by " + Descriptions.at(4).at(util->RandomNumber(0, Descriptions.at(4).size() - 1)) + ".";
	return des;
}

RoomFactory::~RoomFactory()
{
}
