#include "Battle_System.h"

void Action(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending) {
	if (CalculateHit(attacker, defending)) {
		uint64_t damage_to_hp = CalculateDMG(attacker, defending);
		defending->HP() -= damage_to_hp;
		std::cout << defending->GetType() << " takes " << damage_to_hp << " damage\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}

std::unique_ptr<Character>& Fight(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster) {
	std::vector<Damage> inflicted_damage;
	uint64_t total_inflicted_damage = 0;

	auto turn_pair = TurnOrder(player, monster);

	std::unique_ptr<Character>& attacker = turn_pair.first;
	std::unique_ptr<Character>& defending = turn_pair.second;

	while (attacker->HP() != 0 || defending->HP() != 0) { //Returns the winner
		Action(attacker, defending);
		if (defending->HP() == 0) {
			return attacker;
		}
		std::swap(attacker, defending);
	}
}