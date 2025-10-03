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

enum EffectType {
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

    Character(const int64_t strength_, const int64_t dexterity_, const int64_t vitality_);

    virtual ~Character() = default;

    int64_t& HP();
    int64_t& Str();
    const int64_t& Str() const;
    int64_t& Dex();
    const int64_t& Dex() const;
    int64_t& Vit();
    const int64_t& Vit() const;
    const virtual std::string GetType() const = 0;
    std::list<EffectType> ActiveTargetEffects();
    std::list<EffectType> ActiveSelfEffects();

protected:
    int64_t hp;
    int64_t Strength;
    int64_t Dexterity;
    int64_t Vitality;
    std::list<EffectType> target_effects;
    std::list<EffectType> self_effects;
};

class Monster : public Character {
public:
    Monster();
    Monster(const int64_t& hp, const int64_t& base_damage_, const int64_t& strength_, const int64_t& dexterity_, const int64_t& vitality_, const MonsterType& type_, const Weapon& loot_);
    
    const std::string GetType() const;
    const MonsterType& Type() const;
    const Damage Damage_Value() const;
    const Weapon& Loot() const;

private:
    const int64_t base_damage;
    const MonsterType type;
    const Weapon loot;
};

class Player : public Character{
public:
    Player();
    Player(const int64_t& strength_, const int64_t& dexterity_, const int64_t& vitality_, const CharClass& st_class_);
    
    const std::string GetType() const;
    int64_t& Rogue_level();
    int64_t& Warrior_level();
    int64_t& Barbarian_level();
    const int64_t TotalLevel() const;
    Weapon& CurrentWeapon();
    const Weapon& CurrentWeapon() const;

    void LevelUp();
    void OfferWeapon(std::shared_ptr<Monster> monster);

private:
    const int64_t PlayerLevel() const;
    void RogueLevelUp();
    void WarriorLevelUp();
    void BarbarianLevelUp();
    int64_t rogue_level;
    int64_t warrior_level;
    int64_t barbarian_level;
    Weapon weapon;
};

std::ostream& operator<<(std::ostream& os, MonsterType type);