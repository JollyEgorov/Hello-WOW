#pragma once

#include "Character.h"
#include <utility>

bool CalculateHit(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending);

uint64_t CalculateDMG(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending);

std::pair<std::unique_ptr<Character>&, std::unique_ptr<Character>&> TurnOrder(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster);
