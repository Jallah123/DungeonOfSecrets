#pragma once

using namespace std;

class Utility
{
public:
	static Utility* GetInstance();
	int RandomNumber(int min, int max);
private:
	Utility();
	~Utility();
	static Utility* instance;
};