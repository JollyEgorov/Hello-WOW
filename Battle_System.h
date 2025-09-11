#pragma once
#include <vector>
#include "Damage.h"
#include "Character.h"
#include "Character_turn.h"

void Fight(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster);