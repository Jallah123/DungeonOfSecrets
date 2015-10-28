#include "Character.h"
#include "HPPotion.h"
#include "MPPotion.h"
#include "HMPPotion.h"
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

void Character::AddXP(int _XP) {
	XP += _XP;
	if (XP > Level) {
		LevelUp();
	}
}

void Character::LevelUp() {
	Level++;
	XP = 0;
	HP += 10;
	CurrentHP = HP;
	BaseAttack += 5;
	BaseDefence += 5;
	Perception += 1;
}