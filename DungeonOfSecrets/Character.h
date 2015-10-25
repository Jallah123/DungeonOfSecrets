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
		Perception = 1;
		BaseAttack = 100;
		BaseDefence = 100;
		y = Utility::GetInstance()->RandomNumber(0, 4);
		x = Utility::GetInstance()->RandomNumber(0, 4);
		CurrentHP = HP;
	};
	Character(string _Name, int _Level, int _HP, int _MP, int _XP, int _BaseAttack, int _BaseDefence) { Name = _Name; Level = _Level; HP = _HP; MP = _MP; XP = _XP; BaseAttack = _BaseAttack; BaseDefence = _BaseDefence; CurrentHP = HP; };
	~Character();
	void Move(int _X, int _Y) { x = _X; y = _Y; };
	int GetX() { return x; };
	int GetY() { return y; };
	int GetBaseAttack() { return BaseAttack; };
	int GetBaseDefence() { return BaseDefence; };
	Weapon GetWeapon() { return CurrentWeapon; };
	Armour GetArmour() { return CurrentArmour; };
	bool Attack(Character& enemy);
	void AddXP(int _XP);
	int GetLevel() { return Level; };
	void Heal(int _HP) { CurrentHP += _HP; if (CurrentHP > HP) CurrentHP = HP; };
	void DrainMP(int _MP) { MP -= _MP; if (MP < 0) MP = 0; };
	void UseItem(Item& item) { item.DoAction(); };
	void Print() { cout << Name << " HP:" << CurrentHP << " Level: " << Level << endl; };
	void ShowBag();
	bool Damage(int dmg);
	int GetCurrentHP() { return CurrentHP; };
	int GetHP() { return HP; };
	int GetMP() { return MP; };
	int GetPerception() { return Perception; };
	void EquipArmour(Armour& armour) { CurrentArmour = armour; };
	void EquipWeapon(Weapon& weapon) { CurrentWeapon = weapon; };
	string GetName() { return Name; };
	//void AddToBag(Item& item) { Bag.push_back(item); };
private:
	string Name;
	int x;
	int y;
	int Level;
	int CurrentHP;
	int HP;
	int MP;
	int XP;
	int BaseAttack;
	int BaseDefence;
	int Perception;
	Weapon CurrentWeapon;
	Armour CurrentArmour;
	void LevelUp();
	//vector<Item> Bag;
};

