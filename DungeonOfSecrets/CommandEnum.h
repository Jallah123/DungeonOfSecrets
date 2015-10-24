#pragma once
#include <map>

static enum Commands {
	go,
	attack,
	use,
	spell,
	lookatmap,
	bag,
	cheat,
	save,
	load
};

static std::map<std::string, Commands> s_mapStringValues;

void initialize() {
	s_mapStringValues["go"] = go;
	s_mapStringValues["attack"] = attack;
	s_mapStringValues["use"] = use;
	s_mapStringValues["spell"] = spell;
	s_mapStringValues["map"] = lookatmap;
	s_mapStringValues["bag"] = bag;
	s_mapStringValues["inventory"] = bag;
	s_mapStringValues["iamnotworthy"] = cheat;
	s_mapStringValues["save"] = save;
	s_mapStringValues["load"] = load;
}