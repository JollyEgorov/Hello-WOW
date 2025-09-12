#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include "Damage.h"
#include "Character.h"
#include "Character_turn.h"

void Action(std::unique_ptr<Character>& attacker, std::unique_ptr<Character>& defending);

std::unique_ptr<Character>& Fight(std::unique_ptr<Character>& player, std::unique_ptr<Character>& monster);