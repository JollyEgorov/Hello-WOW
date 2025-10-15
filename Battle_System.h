#pragma once
#include <vector>
#include <thread>
#include <chrono>
//#include "Damage.h"
#include "Character.h"
#include "Language.h"
#include "Character_turn.h"

void Action(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defending);

std::shared_ptr<Character> Fight(std::shared_ptr<Player> player, std::shared_ptr<Monster> monster);