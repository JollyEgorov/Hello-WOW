#pragma once
#include "Character_creator.h"
#include "Spawn_monster.h"

std::unique_ptr<Character> Spawn_player();

std::unique_ptr<Character> Spawn_monster();