#pragma once
#include <string>
#include <vector>

using namespace std;

class RoomFactory
{
public:
	static RoomFactory* GetInstance();
	string GetDescription();
private:
	static RoomFactory* instance;	
	vector<vector<string>> Descriptions;
	RoomFactory();
	~RoomFactory();
};