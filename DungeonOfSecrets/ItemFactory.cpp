#include "ItemFactory.h"
#include "Parser.h"
#include "Weapon.h"
#include "Armour.h"
#include "HPPotion.h"
#include "MPPotion.h"
#include "HMPPotion.h"
#include "Misc.h"
#include "Utility.h"
#include <string>

ItemFactory* ItemFactory::instance{ nullptr }; // definition & init

ItemFactory::ItemFactory()
{
	GenerateItems();
}

ItemFactory* ItemFactory::GetInstance() {
	if (instance == nullptr) {
		instance = new ItemFactory;
	}
	return instance;
}

Item* ItemFactory::GetRandomItem()
{
	//int number = Utility::GetInstance()->RandomNumber(0, Items.size()-1);
	int number = 3;
	Item* i = Items.at(number);
}

void ItemFactory::GenerateItems() {
	vector<vector<string>> items = Parser::Parse("Items.txt");
	for (auto &elements : items) {
		string name = elements[0];
		string type = elements[1];
		int value = stoi(elements[2]);
		Item* i = nullptr;
		if (type == "hppotion") {
			i = new HPPotion{ name, value };
		}
		else if (type == "mppotion") {
			i = new MPPotion{ name, value };
		}
		else if (type == "hmppotion") {
			i = new HMPPotion{ name, value };
		}
		else if (type == "weapon") {
			i = new Weapon{ name, value };
		}
		else if (type == "armour") {
			i = new Armour{ name, value };
		}
		else if (type == "misc") {
			i = new Misc{ name };
		}
		Items.push_back(i);
	}
}

ItemFactory::~ItemFactory()
{
}
