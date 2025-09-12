#include "Character_turn.h"

Damage SubstractDMG(const std::list<Damage> dlist, DamageType dt, Damage ddealt) {
	const auto& pos = std::find_if(begin(dlist), end(dlist), [&dt](const Damage& dmg) {return dmg.DType() == dt;});
	return Damage(dt, ddealt.DValue() - pos->DValue());
}

bool CalculateHit(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending) {
	uint64_t rand = Random(1, attacker->Dex() + defending->Dex());
	if (rand <= defending->Dex()) return false;
	return true;
}

uint64_t CalculateDMG(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending) {
	uint64_t calc_result = 0;

	std::list<Damage> off_effects = OffEffectsCheck(attacker, defending);
	std::list<Damage> def_effects = DefEffectsCheck(defending, defending, off_effects);
	std::list<Damage> resulting_dmg;

	for (const auto& dmg : off_effects) {
		switch (dmg.DType()) {
		case DamageType::Cutting:
			resulting_dmg.push_back(SubstractDMG(off_effects, DamageType::Cutting, dmg));
			break;
		case DamageType::Piercing:
			resulting_dmg.push_back(SubstractDMG(off_effects, DamageType::Piercing, dmg));
			break;
		case DamageType::Blunt:
			resulting_dmg.push_back(SubstractDMG(off_effects, DamageType::Blunt, dmg));
			break;
		case DamageType::Pure:
			resulting_dmg.push_back(SubstractDMG(off_effects, DamageType::Pure, dmg));
			break;
		}
	}
	
	for (const auto& dmg : resulting_dmg) {
		calc_result += dmg.DValue();
	}
	
	if (calc_result < 0) return 0;
	return calc_result;
}

std::pair<std::unique_ptr<Character>&, std::unique_ptr<Character>&> TurnOrder(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster) {
	if (player->Dex() >= monster->Dex()) return std::pair<std::unique_ptr<Character>&, std::unique_ptr<Character>&>(player, monster);
	else return std::pair<std::unique_ptr<Character>&, std::unique_ptr<Character>&>(monster, player);
}
