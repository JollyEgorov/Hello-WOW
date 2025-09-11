#include "Battle_System.h"

void Action(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending) {
	if (CalculateHit(attacker, defending)) {
		uint64_t damage_to_hp = CalculateDMG(attacker, defending);
		}
	}

void Fight(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster) {
	std::vector<Damage> inflicted_damage;
	uint64_t total_inflicted_damage = 0;
	
	auto turn_pair = TurnOrder(player, monster);

	std::unique_ptr<Character>& attacker = turn_pair.first;
	std::unique_ptr<Character>& defending = turn_pair.second;

	Action(attacker, defending);
	
	std::swap(attacker, defending);

	Action(attacker, defending);
	/*
	for (Damage& i : inflicted_damage) {
		total_inflicted_damage += i.DValue();
	}*/
}