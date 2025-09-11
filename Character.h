#pragma once
#include <list>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>
#include <utility>

#include "Utility.h"
#include "Weapons.h"
#include "GameState.h"

enum CharClass {
    Rogue,
    Warrior,
    Barbarian,
    None
};

enum MonsterType {
    Goblin,
    Skeleton,
    Slime,
    Ghost,
    Golem,
    Dragon
};

enum Effect {
    enumBackStab,
    enumPoisoned,
    enumToAction,
    enumShield,
    enumFury,
    enumStoneSkin,
    enumSkeleton_skill,
    enumSlime_skill,
    enumDragon_skill
};

class Character {
public:
    Character();

    Character(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_);

    virtual ~Character() = default;

    uint64_t& HP();
    uint64_t& Str();
    uint64_t& Dex();
    uint64_t& Vit();

protected:
    uint64_t hp;
    uint64_t Strength;
    uint64_t Dexterity;
    uint64_t Vitality;
    std::list<Effect> effects;
};

class Player : public Character{
public:
    Player();
    Player(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, const CharClass& st_class_);

    uint64_t& Rogue_level();
    uint64_t& Warrior_level();
    uint64_t& Barbarian_level();
    Weapon& CurrentWeapon();

    const uint64_t& TotalLevel() const;

private:
    uint64_t rogue_level;
    uint64_t warrior_level;
    uint64_t barbarian_level;
    Weapon weapon;
};

class Monster : public Character {
public:
    Monster();
    Monster(const uint64_t& hp, uint64_t base_damage_, const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, MonsterType type_, Weapon loot_);
    
    const MonsterType& Type();
    const uint64_t& Damage();
    const Weapon& Loot();

private:
    const uint64_t base_damage;
    const MonsterType type;
    const Weapon loot;
};
/*
std::ostream& operator<<(std::ostream& os, CharClass cclass) { //Why can't I move it to the other file?
    switch (cclass) {
    case CharClass::Rogue:
        os << "rogue";
        break;
    case CharClass::Warrior:
        os << "warrior";
        break;
    case CharClass::Barbarian:
        os << "barbarian";
        break;
    case CharClass::None:
        os << "none";
        break;
    default:
        os << "Unknown character class!"; // Handle unexpected values
        break;
    }
    return os;
}
*/

std::ostream& operator<<(std::ostream& os, MonsterType type);
