#pragma once
#include <map>

enum Commands {
	go,
	attack,
	use,
	spell,
	lookatmap,
	bag,
	cheat,
	save,
	load,
	help
};

static std::map<std::string, Commands> CommandsMap;

static void InitializeCommands() {
	CommandsMap["go"] = go;
	CommandsMap["attack"] = attack;
	CommandsMap["use"] = use;
	CommandsMap["spell"] = spell;
	CommandsMap["map"] = lookatmap;
	CommandsMap["bag"] = bag;
	CommandsMap["inventory"] = bag;
	CommandsMap["iamnotworthy"] = cheat;
	CommandsMap["save"] = save;
	CommandsMap["load"] = load;
	CommandsMap["help"] = help;
}