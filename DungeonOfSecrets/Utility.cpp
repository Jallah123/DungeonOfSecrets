#include "Utility.h"
#include <iostream>
#include <random>

Utility::Utility()
{
}


Utility::~Utility()
{
}

Utility* Utility::instance{ nullptr }; // definition & init

Utility* Utility::GetInstance() {
	if (instance == nullptr) {
		instance = new Utility;
	}
	return instance;
}

int Utility::RandomNumber(int min, int max) 
{
	random_device dev;
	default_random_engine dre{ dev() };
	uniform_int_distribution<int> dist{ min, max };

	return dist(dre);
}