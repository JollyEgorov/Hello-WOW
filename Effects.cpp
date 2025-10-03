#include "Effects.h"

std::list<Damage> BeautifyEffects(const std::list<Damage>& temp_eff_dmg) {
    std::list<Damage> result_eff_dmg;

    Damage cut(DamageType::Cutting, 0);
    Damage pierce(DamageType::Piercing, 0);
    Damage blunt(DamageType::Blunt, 0);
    Damage pure(DamageType::Pure, 0);

    for (const auto& dmg : temp_eff_dmg) {
        switch (dmg.DType()) {
        case DamageType::Cutting:
            cut.DValue() += dmg.DValue();
            break;
        }
        switch (dmg.DType()) {
        case DamageType::Piercing:
            pierce.DValue() += dmg.DValue();
            break;
        }
        switch (dmg.DType()) {
        case DamageType::Blunt:
            blunt.DValue() += dmg.DValue();
            break;
        }
        switch (dmg.DType()) {
        case DamageType::Pure:
            pure.DValue() += dmg.DValue();
            break;
        }

    }
    result_eff_dmg.push_back(cut);
    result_eff_dmg.push_back(pierce);
    result_eff_dmg.push_back(blunt);
    result_eff_dmg.push_back(pure);

    //if (pure.DValue() < 0) std::cerr << "Damage blocked = " << pure << '\n'; //DEBUG

    return result_eff_dmg;
}

std::list<Damage> OffEffectsCheck(std::shared_ptr<Character> entity, std::shared_ptr<Character> opposing_entity) {
    std::list<Damage> result_eff_dmg;

    if (!entity || !opposing_entity) {
        return result_eff_dmg;  // nullptr protection
    }

    //ƒобавл€ем урон от оружи€ (+ значение силы персонажа) 
    if (Player* player = dynamic_cast<Player*>(entity.get())) {
        result_eff_dmg.push_back(Damage(player->CurrentWeapon().DType(), (player->CurrentWeapon().DValue() + player->Str())));
        //std::cerr << "Weapon damage = " << result_eff_dmg.front().DValue() << '\n';                                             //DEBUG
    }
    else if (Monster* monster = dynamic_cast<Monster*>(entity.get())) {
        result_eff_dmg.push_back(Damage(DamageType::Pure, (monster->Damage_Value()).DValue() + monster->Str()));
        //std::cerr << "Monster damage = " << result_eff_dmg.front().DValue() << '\n';          //DEBUG!
    }
    else {
        std::cerr << "Non player/monster character spotted!!!!!!!!!\n";
    }

    if (!entity->ActiveTargetEffects().empty()) {
        for (const auto& effect : entity->ActiveTargetEffects()) {
            switch (effect) {
            case EffectType::enumBackStab:
                result_eff_dmg.push_back(BackStab(entity, opposing_entity));
                break;
            case EffectType::enumPoisoned:
                result_eff_dmg.push_back(Poisoned());
                break;
            case EffectType::enumToAction:
                if (auto player = dynamic_cast<Player*>(entity.get())) {
                    result_eff_dmg.push_back(ToAction(player));
                }
                else if (auto monster = dynamic_cast<Monster*>(entity.get())) {
                    result_eff_dmg.push_back(ToAction(monster));
                }
                break;
            case EffectType::enumFury:
                result_eff_dmg.push_back(Fury());
                break;
            case EffectType::enumDragon_skill:
                result_eff_dmg.push_back(Dragon_skill());
                break;
            default:
                break;
            }
        }
    }

    return BeautifyEffects(result_eff_dmg);
}

std::list<Damage> DefEffectsCheck(std::shared_ptr<Character> entity, std::shared_ptr<Character> opposing_entity, std::list<Damage>& att_effects) {
    std::list<Damage> result_eff_dmg_red;

    if (!entity || !opposing_entity) {
        return result_eff_dmg_red; // nullptr protection
    }

    if (!entity->ActiveSelfEffects().empty()) {
        for (const auto& effect : entity->ActiveSelfEffects()) {
            switch (effect) {
            case EffectType::enumShield:
                result_eff_dmg_red.push_back(Shield(*entity, *opposing_entity));
                break;
            case EffectType::enumStoneSkin:
                result_eff_dmg_red.push_back(StoneSkin(*entity));
                break;
            case EffectType::enumSkeleton_skill:
                for (auto& att_effect : att_effects) {                              //up to <effects number> iterations - now it's 4
                    result_eff_dmg_red.push_back(Skeleton_skill(att_effect));
                }
                break;
            case EffectType::enumSlime_skill:
                for (auto& att_effect : att_effects) if (att_effect.DType() == DamageType::Cutting) Slime_skill(att_effect); //also up to <effects number> iterations - now it's 4
                break;
            default:
                break;
            }
        }
    }
    /*else {                                                                           //DEBUG
        std::cerr << "No active defensive effects!\n";
    }*/

    return BeautifyEffects(result_eff_dmg_red);
}

Damage BackStab(const std::shared_ptr<Character> self, const std::shared_ptr<Character> target) {
    if (self->Dex() > target->Dex()) {
        return Damage(DamageType::Pure, 1);
    }
    return Damage();
}

Damage Poisoned() {
    int64_t poison_damage = GameState::getInstance().getTurn() - 1;
    if (poison_damage < 0) return Damage();
    return Damage(DamageType::Pure, poison_damage);
}

Damage ToAction(Player* self) { //Weapon needed for skill usage. Weapons can be held only by the player
    if (GameState::getInstance().getTurn() == 0) {
        return Damage(DamageType::Pure, self->CurrentWeapon().DValue());
    }
    return Damage();
}
Damage ToAction(Monster* self) { //Weapon not needed for skill usage. Weapons can be held only by the player
    if (GameState::getInstance().getTurn() == 0) {
        int64_t dvalue = self->Damage_Value().DValue();
        return Damage(DamageType::Pure, dvalue);
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

Damage Skeleton_skill(const Damage& dmg_taken) {
    if (dmg_taken.DType() == DamageType::Blunt) {
        Damage ddamage(DamageType::Blunt, dmg_taken.DValue() * (-1));
        return ddamage;
    }
    return Damage(DamageType::Pure, 0);
}

Damage Slime_skill(const Damage& dmg_taken) {
    if (dmg_taken.DType() == DamageType::Cutting) {
        Damage ddamage(DamageType::Blunt, dmg_taken.DValue());
        return ddamage;
    }
    return Damage(DamageType::Pure, 0);
}

Damage Dragon_skill() {
    if ((GameState::getInstance().getTurn() % 3) == 0) {
        return Damage(DamageType::Pure, 3);
    }
    return Damage();
}