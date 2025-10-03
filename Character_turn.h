#pragma once
#include <utility>
#include <algorithm>

#include "Character.h"
#include "Effects.h"

Damage SubstractDMG(const std::list<Damage>::iterator pos, Damage dblocked);

bool CalculateHit(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defending);

int64_t CalculateDMG(std::shared_ptr<Character>& attacker, std::shared_ptr<Character>& defending);

std::pair<std::shared_ptr<Character>, std::shared_ptr<Character>> TurnOrder(std::shared_ptr<Player> player, std::shared_ptr<Monster> monster);
