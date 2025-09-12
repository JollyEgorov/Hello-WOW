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

    return result_eff_dmg;
}

std::list<Damage> OffEffectsCheck(const std::unique_ptr<Character>& entity, const std::unique_ptr<Character>& opposing_entity) {
    std::list<Damage> result_eff_dmg;
    
    //ƒобавл€ем урон от оружи€ + значение силы персонажа
    if (typeid(*entity) == typeid(Player)) {
        result_eff_dmg.push_back(Damage(entity->CurrentWeapon().DType(), (entity->CurrentWeapon().DValue() + entity->Str())));
        std::cerr << "Weapon damage = " << result_eff_dmg.front().DValue() << '\n';
    }
    else if (typeid(*entity) == typeid(Monster)) {
        result_eff_dmg.push_back(Damage(DamageType::Pure, entity->Damage()));
        std::cerr << "Monster damage = " << result_eff_dmg.front().DValue() << '\n';
    }
    else {
        std::cerr << "Non player/monster character spotted!!!!!!!!!\n";
    }

    if (!entity || !opposing_entity) {
        return result_eff_dmg;  // nullptr protection
    }

    if (!entity->ActiveOffEffects().empty()) {
        for (const auto& effect : entity->ActiveOffEffects()) {
            switch (effect) {
            case EffectType::enumBackStab :
                result_eff_dmg.push_back(BackStab(*entity, *opposing_entity));
                break;
            case EffectType::enumPoisoned :
                result_eff_dmg.push_back(Poisoned());
                break;
            case EffectType::enumToAction :
                result_eff_dmg.push_back(ToAction(*entity));
                break;
            case EffectType::enumFury :
                result_eff_dmg.push_back(Fury());
                break;
            case EffectType::enumDragon_skill :
                result_eff_dmg.push_back(Dragon_skill());
                break;
            default:
                break;
            }
        }
    }
    return BeautifyEffects(result_eff_dmg);
}

std::list<Damage> DefEffectsCheck(std::unique_ptr<Character>& entity, std::unique_ptr<Character>& opposing_entity, std::list<Damage>& att_effects) {
    std::list<Damage> result_eff_dmg_red;

    if (!entity || !opposing_entity) {
        return result_eff_dmg_red; // nullptr protection
    }

    if (!entity->ActiveDefEffects().empty()) {
        for (const auto& effect : entity->ActiveDefEffects()) {
            switch (effect) {
            case EffectType::enumShield:
                result_eff_dmg_red.push_back(Shield(*entity, *opposing_entity));
                break;
            case EffectType::enumStoneSkin:
                result_eff_dmg_red.push_back(StoneSkin(*entity));
                break;
            case EffectType::enumToAction:
                result_eff_dmg_red.push_back(ToAction(*entity));
                break;
            case EffectType::enumSkeleton_skill:

                for (auto& att_effect : att_effects) {
                    result_eff_dmg_red.push_back(Skeleton_skill(att_effect));
                    if (att_effect.DType() == DamageType::Blunt) Skeleton_skill(att_effect); //up to <effects number> iterations - now it's 4
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
    return BeautifyEffects(result_eff_dmg_red);
}

Damage BackStab(const Character& self, const Character& target) {
    if (self.Dex() > target.Dex()) {
        return Damage(DamageType::Pure, 1);
    }
    return Damage();
}

Damage Poisoned() {
    uint64_t poison_damage = GameState::getInstance().getTurn() - 1;
    return Damage(DamageType::Pure, poison_damage);
}

Damage ToAction(Character& self) { //Weapon needed for skill usage. Weapons can be held only by the player now
    if (GameState::getInstance().getTurn() == 1) {
        uint64_t dvalue = self.CurrentWeapon().DValue();
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