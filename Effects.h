#pragma once
#include <memory>
#include <thread>
#include <cstdint>
#include "Character.h"

std::list<Damage> BeautifyEffects(const std::list<Damage>& temp_eff_dmg);

std::list<Damage> OffEffectsCheck(std::shared_ptr<Character> entity, std::shared_ptr<Character> opposing_entity);

std::list<Damage> DefEffectsCheck(std::shared_ptr<Character> entity, std::shared_ptr<Character> opposing_entity, std::list<Damage>& att_effects);

Damage BackStab(const std::shared_ptr<Character> self, const std::shared_ptr<Character> target);
Damage Poisoned();
Damage ToAction(Player* self);
Damage ToAction(Monster* self);
Damage Shield(Character& self, Character& target);
Damage Fury();
Damage StoneSkin(Character& target);
Damage Skeleton_skill(const Damage& dmg_taken);
Damage Slime_skill(const Damage& dmg_taken);
Damage Dragon_skill();