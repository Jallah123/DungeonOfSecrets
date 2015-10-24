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