#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Weapon.h"
#include "Armour.h"
#include "Utility.h"
#include <iostream>

using namespace std;

class Character
{
public:
	Character() {};
	Character(string _Name) {
		Name = _Name;
		Level = 1;
		HP = 10;
		MP = 20;
		XP = 0;
		BaseAttack = 2;
		BaseDefence = 1;
		y = Utility::GetInstance()->RandomNumber(0, 4);
		x = Utility::GetInstance()->RandomNumber(0, 4);
	};
	Character(string _Name, int _Level, int _HP, int _MP, int _XP, int _BaseAttack, int _BaseDefence) { Name = _Name; Level = _Level; HP = _HP; MP = _MP; XP = _XP; BaseAttack = _BaseAttack; BaseDefence = _BaseDefence; };
	~Character();
	void Move(int _X, int _Y) { x = _X; y = _Y; };
	int GetX() { return x; };
	int GetY() { return y; };
	void Attack(Character& enemy) { enemy.Damage(BaseAttack + CurrentWeapon.GetDamage()); };
	void UseItem(Item& item) { item.DoAction(); };
	void Print() { cout << Name << " HP:" << HP << "Level:" << Level << endl; };
	void LookAtMap();
	void ShowBag();
	void Damage(int dmg) { HP -= dmg; };
	void EquipArmour(Armour& armour) { CurrentArmour = armour; };
	void EquipWeapon(Weapon& weapon) { CurrentWeapon = weapon; };
	string GetName() { return Name; };
	//void AddToBag(Item& item) { Bag.push_back(item); };
private:
	string Name;
	int x;
	int y;
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

