#pragma once
#include <thread>
#include <cstdint>
#include "Character.h"

std::list<Damage> BeautifyEffects(const std::list<Damage>& temp_eff_dmg);

std::list<Damage> OffEffectsCheck(const std::unique_ptr<Character>& entity, const std::unique_ptr<Character>& opposing_entity);

std::list<Damage> DefEffectsCheck(std::unique_ptr<Character>& entity, std::unique_ptr<Character>& opposing_entity, std::list<Damage>& att_effects);

Damage BackStab(const Character& self, const Character& target);

Damage Poisoned();

Damage ToAction(Character& target);

Damage Shield(Character& self, Character& target);

Damage Fury();

Damage StoneSkin(Character& target);

Damage Skeleton_skill(const Damage& dmg_taken);

Damage Slime_skill(const Damage& dmg_taken);

Damage Dragon_skill();