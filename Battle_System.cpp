#include "Battle_System.h"

void Action(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defending) {
	if (CalculateHit(attacker, defending)) {
		
		std::cout << attacker->GetType() << Localization::getInstance().getString("ihit") << defending->GetType() << "\n"; //DEBUG?
		
		int64_t damage_to_hp = CalculateDMG(attacker, defending);

		defending->HP() -= damage_to_hp;

		std::cout << defending->GetType() << Localization::getInstance().getString("itakedmg0") 
										  << damage_to_hp 
										  << Localization::getInstance().getString("itakedmg1");

		if (defending->HP() <= 0) std::cout << Localization::getInstance().getString("idie") << '\n';
		else std::cout << '\n';
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	else {
		std::cout << attacker->GetType() << Localization::getInstance().getString("imiss") << defending->GetType() << "\n"; //DEBUG?
		std::this_thread::sleep_for(std::chrono::milliseconds(2000)); 
	}
}

std::shared_ptr<Character> Fight(std::shared_ptr<Player> player, std::shared_ptr<Monster> monster) {
	GameState::getInstance().resetTurn();
	std::vector<Damage> inflicted_damage;
	int64_t total_inflicted_damage = 0;

	auto turn_pair = TurnOrder(player, monster);

	std::shared_ptr<Character> attacker = turn_pair.first;
	std::shared_ptr<Character> defending = turn_pair.second;
	uint64_t swap_number = 0;

	while (attacker->HP() != 0 && defending->HP() != 0) { //Returns the winner
		Action(attacker, defending);
		if (defending->HP() <= 0 || attacker->HP() <=0) {break;}
		std::swap(attacker, defending);
		++swap_number;
		if (swap_number % 2 == 0) {
			GameState::getInstance().nextTurn();
			//std::cerr << "IT'S NOW TURN " << GameState::getInstance().getTurn() << '\n';				//DEBUG?
		}
	}
	return attacker;
}