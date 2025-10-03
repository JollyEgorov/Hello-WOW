#include "Character_turn.h"

Damage SubstractDMG(const std::list<Damage>::iterator pos, Damage dblocked) {
	//std::cerr << "Before substraction: " << *pos << '\n'; //DEBUG
	return Damage(dblocked.DType(), pos->DValue() - dblocked.DValue());
}

bool CalculateHit(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defending) {
	int64_t rand = Random(1, attacker->Dex() + defending->Dex());
	if (rand <= defending->Dex()) {		
		return false;
	}
	return true;
}

int64_t CalculateDMG(std::shared_ptr<Character>& attacker, std::shared_ptr<Character>& defending) {
	int64_t calc_result = 0;

	std::list<Damage> off_effects = OffEffectsCheck(attacker, defending);
	std::list<Damage> def_effects = DefEffectsCheck(defending, attacker, off_effects);
	std::list<Damage> resulting_dmg = {Damage(DamageType::Pure, 0)};

	if (!off_effects.empty()) {
		resulting_dmg = move(off_effects);
	}
	/*
	for (const auto& it : resulting_dmg) {																//DEBUG
		std::cerr << RED_COLOR << "Offensive damage: " << it << RESET_COLOR << '\n';
	}
	for (const auto& it : def_effects) {																//DEBUG
		std::cerr << GREEN_COLOR << "Defensive 'damage': " << it << RESET_COLOR << '\n';
	}*/
	
	if (!def_effects.empty()) {
		for (const auto& dmg : def_effects) {
			const auto& pos = std::find_if(begin(resulting_dmg), end(resulting_dmg),
				[dmg](const Damage& off_dmg) {return dmg.DType() == off_dmg.DType();});					//pos = correlating damage in damage_list
			if (pos != end(resulting_dmg)) {															//Damage found
				*pos = (SubstractDMG(pos, dmg));
				//std::cerr << YELLOW_COLOR << "Substracted damage: " << *pos << RESET_COLOR << '\n';		//DEBUG
			}
			/*else {																						//DEBUG
				std::cerr << YELLOW_COLOR << "UnSubStracted damage: " << dmg << RESET_COLOR << '\n';
			}*/
		}
	}
	
	for (const auto& dmg : resulting_dmg) {
		calc_result += dmg.DValue();
		//std::cout << "dmg.DValue() = " << dmg.DValue() << '\n';
		//std::cout << "Calc result = " << calc_result << '\n';
	}
	
	if (calc_result < 0) return 0;
	return calc_result;
}

std::pair<std::shared_ptr<Character>, std::shared_ptr<Character>> TurnOrder(std::shared_ptr<Player> player, std::shared_ptr<Monster> monster) {
	if (!player || !monster) {
		return { nullptr, nullptr };
	}

	if (player->Dex() >= monster->Dex()) {
		return { player, monster };
	}
	else {
		return { monster, player };
	}
}