#pragma once
#include <cstdint>
#include "Character.h"


Damage BackStab(Character& self, Character& target);

Damage Poisoned();

Damage ToAction(Player& target);

Damage Shield(Character& self, Character& target);

Damage Fury();

Damage StoneSkin(Character& target);

Damage& Skeleton_skill(Damage& dmg_taken);

Damage& Slime_skill(Damage& dmg_taken);

Damage Dragon_skill();