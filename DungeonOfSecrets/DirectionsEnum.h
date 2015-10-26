#pragma once
#include <map>
enum Directions {
	North,
	East,
	South,
	West,
	Down
};

static std::map<std::string, Directions> DirectionsMap;

static void InitializeDirections() {
	DirectionsMap["north"] = North;
	DirectionsMap["east"] = East;
	DirectionsMap["south"] = South;
	DirectionsMap["west"] = West;
	DirectionsMap["down"] = Down;
}

static std::map<Directions, std::string> StringMap;

static void InitializeStrings() {
	StringMap[North] = "North";
	StringMap[East] = "East";
	StringMap[South] = "South";
	StringMap[West] = "West";
	StringMap[Down] = "Down";
}