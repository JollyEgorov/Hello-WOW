#pragma once
#include "Character_creator.h"
#include "Spawn_monster.h"
#include <memory>

std::shared_ptr<Player> Spawn_player();

std::shared_ptr<Monster> Spawn_monster();