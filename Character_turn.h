#pragma once

#include "Character.h"
#include "Effects.h"
#include <utility>

bool CalculateHit(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending);

uint64_t CalculateDMG(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending);

std::pair<Character*, Character*> TurnOrder(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster);
