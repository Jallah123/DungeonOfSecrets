#include "Character.h"
#include <iostream>

Character::~Character()
{
}

void Character::ShowBag() {
	cout << "You look into your bag and see:" <<endl;
//	for each (Item item in Bag)
//	{
//		cout << item.GetName() << endl;
//	}

}

bool Character::Attack(Character& enemy) {
	cout << "" << (BaseAttack + CurrentWeapon.GetDamage()) << " damage dealt to : " << enemy.GetName() << endl; 
	return enemy.Damage(BaseAttack + CurrentWeapon.GetDamage());
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