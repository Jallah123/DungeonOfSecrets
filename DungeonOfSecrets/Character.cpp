#include "Character.h"
#include "HPPotion.h"
#include "MPPotion.h"
#include "HMPPotion.h"
#include "ItemFactory.h"
#include "Parser.h"
#include <iostream>

Character::~Character()
{
}

void Character::UseItem(int i)
{
	Item* item;
	if (i < Bag.size() && i >= 0) {
		item = Bag.at(i);
	}
	else {
		cout << "No such item." << endl;
		return;
	}
	if (Armour* armour = dynamic_cast<Armour*>(item)) {
		EquipArmour(*armour);
	}
	else if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
		EquipWeapon(*weapon);
	}
	else if (HPPotion* hppot = dynamic_cast<HPPotion*>(item)) {
		Heal(hppot->GetValue());
		RemoveFromBag(hppot);
	}
	else if (MPPotion* mppot = dynamic_cast<MPPotion*>(item)) {
		Recharge(mppot->GetValue());
		RemoveFromBag(mppot);
	}
	else if (HMPPotion* hmppot = dynamic_cast<HMPPotion*>(item)) {
		Heal(hmppot->GetValue());
		Recharge(hmppot->GetValue());
		RemoveFromBag(hmppot);
	}
	else {
		cout << "This item is useless..." << endl;
	}
}

void Character::ShowBag() {
	cout << "You look into your bag and see:" << endl;
	int i = 0;
	for each (Item* item in Bag)
	{
		cout << i++ << ". " << item->GetName() << endl;
	}
	if (i == 0) {
		cout << "Nothing." << endl;
	}
}

bool Character::Attack(Character& enemy) {
	int damage = BaseAttack - enemy.GetBaseDefence();
	if (CurrentWeapon != nullptr) {
		damage += CurrentWeapon->GetDamage();
	}
	if (enemy.CurrentArmour != nullptr) {
		damage -= enemy.CurrentArmour->GetDefence();
	}
	if (damage < 0) {
		damage = 0;
	}
	cout << "" << damage << " damage dealt to : " << enemy.GetName() << endl;
	return enemy.Damage(damage);
}

bool Character::Damage(int dmg) {
	CurrentHP -= dmg;
	if (CurrentHP <= 0)
		return true;
	return false;
}

string Character::GetSaveString()
{
	ItemFactory* ItemFactory = ItemFactory::GetInstance();
	string retString = Name + ";" + to_string(Level) + ";" + to_string(HP) + ";" + to_string(MP) + ";" + to_string(XP) + ";" + to_string(BaseAttack) + ";" + to_string(BaseDefence) + ";" + to_string(Perception) + ";";
	retString += to_string(ItemFactory->GetIndexFromItem(CurrentWeapon)) + ";";
	retString += to_string(ItemFactory->GetIndexFromItem(CurrentArmour)) + ";";
	for (auto& item : Bag)
	{
		retString += to_string(ItemFactory::GetInstance()->GetIndexFromItem(item)) + ",";
	}
	retString += ";";
	return retString;
}

void Character::AddXP(int _XP) 
{
	XP += _XP;
	if (XP > Level) {
		LevelUp();
	}
}

void Character::LevelUp() 
{
	Level++;
	XP = 0;
	HP += 10;
	CurrentHP = HP;
	BaseAttack += 5;
	BaseDefence += 5;
	Perception += 1;
}

void Character::Load() 
{
	// Name Level HP MP XP Perception Attack Defence Weapon Armour Bag
	vector<vector<string>> character = Parser::Parse(Name + ".wizard");
	for (auto &elements : character) {
		Level = stoi(elements[1]);
		HP = stoi(elements[2]);
		CurrentHP = HP;
		MP = stoi(elements[3]);
		XP = stoi(elements[4]);
		Perception = stoi(elements[5]);
		BaseAttack = stoi(elements[6]);
		BaseDefence = stoi(elements[7]);
		CurrentWeapon = dynamic_cast<Weapon*>(ItemFactory::GetInstance()->GetItemFromIndex(stoi(elements[8])));
		CurrentArmour = dynamic_cast<Armour*>(ItemFactory::GetInstance()->GetItemFromIndex(stoi(elements[9])));

		vector<string> bag;
		Parser::split(elements[10], ',', bag);

		for (auto& index : bag) 
		{
			AddToBag(ItemFactory::GetInstance()->GetItemFromIndex(stoi(index)));
		}
	}
}