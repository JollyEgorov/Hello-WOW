#include "Spawn_monster.h"


std::unique_ptr<Character> Monster_creation() {
	uint64_t hp = 0;
	uint64_t damage = 0;
	uint64_t strength = 0;
	uint64_t dexterity = 0;
	uint64_t vitality = 0;
	MonsterType type = MonsterType::Goblin;
	Weapon loot(WeaponType::Dagger);

	uint64_t monster_type = Random(0, 5);	//Random enemy
	type = MonsterType(monster_type);
	switch (monster_type) {					//Setting up enemies
		case MonsterType::Goblin : {
			hp = 5;
			damage = 2;
			strength = 1;
			dexterity = 1;
			vitality = 1;
			loot = Weapon(WeaponType::Dagger);
			break;
		}
		case MonsterType::Skeleton: {
			hp = 10;
			damage = 2;
			strength = 2;
			dexterity = 2;
			vitality = 1;
			loot = Weapon(WeaponType::Club);
			break;
		}
		case MonsterType::Slime: {
			hp = 8;
			damage = 1;
			strength = 3;
			dexterity = 1;
			vitality = 2;
			loot = Weapon(WeaponType::Spear);
			break;
		}
		case MonsterType::Ghost: {
			hp = 6;
			damage = 3;
			strength = 1;
			dexterity = 3;
			vitality = 1;
			loot = Weapon(WeaponType::Sword);
			break;
		}
		case MonsterType::Golem: {
			hp = 10;
			damage = 1;
			strength = 3;
			dexterity = 1;
			vitality = 3;
			loot = Weapon(WeaponType::Axe);
			break;
		}
		case MonsterType::Dragon: {
			hp = 20;
			damage = 4;
			strength = 3;
			dexterity = 3;
			vitality = 3;
			loot = Weapon(WeaponType::SwordLeg);
			break;
		}
	}
	std::cout << "Monster " << type << " appears!" << '\n'; //DEBUG?
	return std::make_unique<Monster>(hp, damage, strength, dexterity, vitality, type, loot);
}