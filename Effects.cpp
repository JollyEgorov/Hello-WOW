#include "Effects.h"

Damage BackStab(Character& self, Character& target) {
    if (self.Dex() > target.Dex()) {
        return Damage(DamageType::Pure, 1);
    }
    return Damage();
}

Damage Poisoned() {
    uint64_t poison_damage = GameState::getInstance().getTurn() - 1;
    return Damage(DamageType::Pure, poison_damage);
}

Damage ToAction(Player& self) { //Weapon needen for skill usage. Weapons can be helf only by the player now
    if (GameState::getInstance().getTurn() == 1) {
        return Damage(DamageType::Pure, (self.CurrentWeapon().Damage()));
    }
    return Damage();
}

Damage Shield(Character& self, Character& target) {
    if (self.Str() > target.Str()) {
        return Damage(DamageType::Pure, 3);
    }
    return Damage();
}

Damage Fury() {
    if (GameState::getInstance().getTurn() <= 3) {
        return Damage(DamageType::Pure, 2);
    }
    return Damage(DamageType::Pure, -1);
}

Damage StoneSkin(Character& self) {
    return Damage(DamageType::Pure, self.Vit());
}

Damage& Skeleton_skill(Damage& dmg_taken) {
    if (dmg_taken.DType() == DamageType::Blunt) {
        dmg_taken.DValue() *= 2;
    }
    return dmg_taken;
}

Damage& Slime_skill(Damage& dmg_taken) {
    if (dmg_taken.DType() == DamageType::Cutting) {
        dmg_taken.DValue() *= 0;
    }
    return dmg_taken;
}

Damage Dragon_skill() {
    if ((GameState::getInstance().getTurn() % 3) == 0) {
        return Damage(DamageType::Pure, 3);
    }
}