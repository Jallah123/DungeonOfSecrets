#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Weapon.h"
#include "Armour.h"

using namespace std;

class Character
{
public:
	Character() {};
	Character(string _Name, int _Level, int _HP, int _MP, int _XP, int _BaseAttack, int _BaseDefence) { Name = _Name; Level = _Level; HP = _HP; MP = _MP; XP = _XP; BaseAttack = _BaseAttack; BaseDefence = _BaseDefence; };
	~Character();
	void Attack(Character& enemy) { enemy.Damage(BaseAttack + CurrentWeapon.GetDamage()); };
	void UseItem(Item& item) { item.DoAction(); };
	void LookAtMap();
	void ShowBag();
	void Damage(int dmg) { HP -= dmg; };
	void EquipArmour(Armour& armour) { CurrentArmour = armour; };
	void EquipWeapon(Weapon& weapon) { CurrentWeapon = weapon; };
	//void AddToBag(Item& item) { Bag.push_back(item); };
private:
	string Name;
	int Level;
	int HP;
	int MP;
	int XP;
	int BaseAttack;
	int BaseDefence;
	int Perception;
	Weapon CurrentWeapon;
	Armour CurrentArmour;
	//vector<Item> Bag;
};

