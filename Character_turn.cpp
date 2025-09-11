#include "Character_turn.h"

bool CalculateHit(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending) {
	uint64_t rand = Random(1, attacker->Dex() + defending->Dex());
	if (rand <= defending->Dex()) return false;
	return true;
}

uint64_t CalculateDMG(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending) {
	uint64_t calc_result = 0;

	if (calc_result == 0) return 0;
	return 0;
}

std::pair<std::unique_ptr<Character>&, std::unique_ptr<Character>&> TurnOrder(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster) {
	if (player->Dex() >= monster->Dex()) return std::pair<std::unique_ptr<Character>&, std::unique_ptr<Character>&>(player, monster);
	else return std::pair<std::unique_ptr<Character>&, std::unique_ptr<Character>&>(monster, player);
}
