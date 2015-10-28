#pragma once
#include <map>

enum Commands {
	go,
	attack,
	use,
	spell,
	look,
	bag,
	cheat,
	save,
	load,
	help,
	rest,
	info,
	talisman,
	showmap,
	openmap,
	compass,
	spawnsuperboss,
	pickup,
};

static std::map<std::string, Commands> CommandsMap;

static void InitializeCommands() {
	CommandsMap["go"] = go;
	CommandsMap["attack"] = attack;
	CommandsMap["use"] = use;
	CommandsMap["spell"] = spell;
	CommandsMap["look"] = look;
	CommandsMap["bag"] = bag;
	CommandsMap["inventory"] = bag;
	CommandsMap["iamnotworthy"] = cheat;
	CommandsMap["showmap"] = showmap;
	CommandsMap["save"] = save;
	CommandsMap["load"] = load;
	CommandsMap["help"] = help;
	CommandsMap["rest"] = rest;
	CommandsMap["info"] = info;
	CommandsMap["talisman"] = talisman;
	CommandsMap["compass"] = compass;
	CommandsMap["openmap"] = openmap;
	CommandsMap["spawnsuperboss"] = spawnsuperboss;
	CommandsMap["pickup"] = pickup;
}